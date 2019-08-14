#include "stdafx.h"
#include "cMain.h"
#include "cCamera.h"
#include "cCube.h"
#include "cLight.h"
#include "cSphere.h"
#include "cTorus.h"
#include "cLoader.h"
#include "cMesh.h"
#include "cGrid.h"
#include "cPyramid.h"
#include "cTriangle.h"
#include <algorithm>
#include <map>
cMain::cMain()
{
}


cMain::~cMain()
{
}

HRESULT cMain::Init()
{
	m_pCamera = new cCamera;
	m_pCamera->init();

	m_pDirectionLight = new cLight;
	m_pDirectionLight->init();

	CRect rc;
	GetClientRect(g_hWnd, &rc);

	vp = jbMath::Viewport(0, 0, rc.right, rc.bottom, 0, 1);

	m_isClick = isMoving = false;

	m_pCurrentFigure = nullptr;
	m_pCurrentMesh = nullptr;
	m_nFigureNum = -1;

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	axis = -1;

//	m_pNC = new cnewCube;
//	m_pNC->init();

	jbUtill::SetFrustum();

	return E_NOTIMPL;
}

void cMain::Update()
{
	if (m_isClick)
	{
		m_isClick = false;
		CRect rc;
		GetClientRect(g_hWnd, &rc);
		auto ray = m_pCamera->GetRay(m_ptMouse, rc);
		
		for (int i = 0; i < m_vFigures.size(); ++i)
		{
			//if (jbUtill::ComputeRayCast(ray, m_vFigures[i]->GetPyramid(), axis, m_vFigures[i]->GetWorld()))
			//{
			//	isMoving = true;
			//	return;
			//}
			if (jbUtill::ComputeRayCast(ray, m_vFigures[i]))
			{
				m_pCurrentFigure = m_vFigures[i];
				m_pCurrentMesh = nullptr;
				m_nFigureNum = -1;
			}
		}
		for (int i = 0; i < m_vMesh.size(); ++i)
		{
			if (jbUtill::ComputeRayCast(ray, m_vMesh[i]))
			{
				m_pCurrentMesh = m_vMesh[i];
				m_pCurrentFigure = nullptr;
				m_nFigureNum = -1;
			}
		}
		auto createSet = ray.ori + ray.dir * (jbMath::Vector3(0,0,0) - m_pCamera->pos).Length();
		auto mat = jbMath::Translation(&createSet);
		switch (m_nFigureNum)
		{
		case 0:
			m_pCurrentFigure = new cCube;
			m_pCurrentFigure->Init();
			m_pCurrentFigure->SetPosition(createSet);
			m_vFigures.push_back(m_pCurrentFigure);
			m_pCurrentMesh = nullptr;
			break;
		case 1:
			m_pCurrentFigure = new cSphere;
			m_pCurrentFigure->Init();
			m_pCurrentFigure->SetPosition(createSet);
			m_vFigures.push_back(m_pCurrentFigure);
			m_pCurrentMesh = nullptr;
			break;
		case 2:
			m_pCurrentFigure = new cTorus;
			m_pCurrentFigure->Init();
			m_pCurrentFigure->SetPosition(createSet);
			m_vFigures.push_back(m_pCurrentFigure);
			m_pCurrentMesh = nullptr;
			break;
		case 4:
			m_pCurrentFigure = new cTriangle;
			m_pCurrentFigure->Init();
			m_pCurrentFigure->SetPosition(createSet);
			m_vFigures.push_back(m_pCurrentFigure);
			m_pCurrentMesh = nullptr;
			break;
		case 3:
			int n = str.GetLength();
			char* s = new char[n];
			strcpy(s, str.GetBuffer(0));
			str.ReleaseBuffer();

 			m_pCurrentMesh = cLoader::OBJLoader(s);
			m_pCurrentMesh->init();
			m_vMesh.push_back(m_pCurrentMesh);
			m_pCurrentFigure = nullptr;
			break;
		}
		//m_nFigureNum = -1;
	}
	z_order.clear();
	for (int i = 0; i < m_vFigures.size(); ++i)
	{
		m_vFigures[i]->update();
		auto vec = m_vFigures[i]->GetPosition();
		
		vec = vec.TransformCoord(&m_vFigures[i]->GetWorld());
		vec = vec.TransformCoord(&m_pCamera->GetViewProj());
		vec = vec.TransformCoord(&vp);

		z_order[vec.z] = i;
	}
	for (int i = 0; i < m_vMesh.size(); ++i)
		m_vMesh[i]->update();
	if(m_pCurrentFigure)
		m_pCurrentFigure->Moving();
	if (m_pCurrentMesh)
		m_pCurrentMesh->Moving();
	m_pCamera->update();
	m_pDirectionLight->update();
}

void cMain::Release()
{
}

void cMain::Draw(CDC* pDC)
{
	m_pGrid->draw(pDC, *m_pCamera, vp);
	auto iter = z_order.rbegin();
	auto e = z_order.rend();
	for (; iter != e; ++iter)
	{
		if (m_pCurrentFigure)
		{
			if (m_vFigures[(*iter).second] == m_pCurrentFigure)
			{
				auto p = dynamic_cast<cTriangle*>(m_pCurrentFigure);
				if (p)
					m_pCurrentFigure->SelectDraw(pDC, *m_pCamera, vp, m_pDirectionLight);
				else if (jbUtill::FrustumCulling(m_pCurrentFigure, m_pCamera->GetViewProj()))
					m_pCurrentFigure->SelectDraw(pDC, *m_pCamera, vp, m_pDirectionLight);
				continue;
			}
		}
		auto p = dynamic_cast<cTriangle*>(m_vFigures[(*iter).second]);
		if (p)
			m_vFigures[(*iter).second]->draw(pDC, *m_pCamera, vp, m_pDirectionLight);
		else if (jbUtill::FrustumCulling(m_vFigures[(*iter).second], m_pCamera->GetViewProj()))
			m_vFigures[(*iter).second]->draw(pDC, *m_pCamera, vp, m_pDirectionLight);
	}
	for (int i = 0; i < m_vFigures.size(); ++i)
	{
		if (m_pCurrentFigure == m_vFigures[i]) continue;
		if (!m_pCurrentFigure) continue;
		if (!m_pCurrentFigure->GetBondbox() || !m_vFigures[i]->GetBondbox()) continue;

		auto pA = dynamic_cast<cSphere*>(m_vFigures[i]);
		auto pB = dynamic_cast<cSphere*>(m_pCurrentFigure);
		if (m_pCurrentFigure)
		{
			if (pA && pB)
			{
				if (jbUtill::SphereCollision(m_vFigures[i]->GetBondbox(), m_pCurrentFigure->GetBondbox()))
				{
					pDC->TextOutA(0, 0, "sphere 충돌!!");
				}
			}
			else if (jbUtill::AABBCollision(m_vFigures[i]->GetBondbox(), m_pCurrentFigure->GetBondbox()))
			{
				pDC->TextOutA(0, 0, "AABB충돌!!");
				if (jbUtill::OBBCollision(m_vFigures[i], m_pCurrentFigure))
				{
					pDC->TextOutA(0, 15, "OBB충돌!!");
				}
			}
		}
	}
	for (int i = 0; i < m_vMesh.size(); ++i)
	{
		if (m_pCurrentMesh == m_vMesh[i]) continue;
		m_vMesh[i]->draw(pDC, *m_pCamera, vp, m_pDirectionLight);
	}
	if (m_pCurrentMesh)
		m_pCurrentMesh->SelectDraw(pDC, *m_pCamera, vp, m_pDirectionLight);

//	m_pNC->draw(pDC, *m_pCamera, vp);
}

void cMain::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);

	switch (message)
	{
	case WM_LBUTTONDOWN:
		m_isClick = true;
		m_ptMouse.x = LOWORD(lParam);
		m_ptMouse.y = HIWORD(lParam);
		break;
	case WM_LBUTTONUP:
		m_isClick = false;
		isMoving = false;
		axis = -1;
		break;
	case WM_MOUSEMOVE:
		if (isMoving)
		{
			int px;// = LOWORD(lParam);
			float x = 0;

			jbMath::Vector3 pos = m_pCurrentFigure->GetPosition();
			jbMath::Vector3 dir(0, 0, 0);
			switch (axis)
			{
			case 0: case 3: case 6:
				px = LOWORD(lParam);
				x = (m_ptMouse.x - px);
				dir = jbMath::Vector3(x, 0, 0);
				break;
			case 9: case 12: case 15:
				px = HIWORD(lParam);
				x = (m_ptMouse.x - px);
				dir = jbMath::Vector3(0, x, 0);
				break;
			case 18: case 21: case 24:
				px = LOWORD(lParam);
				x = (m_ptMouse.x - px);
				dir = jbMath::Vector3(0, 0, x);
				break;
			}

			if (!dir.ZeroVector())
			{
				dir = -dir.Normalize();
				m_pCurrentFigure->SetPosition(pos + dir * 0.1f);
			}
		}
		break;
	}
}

void cMain::SetParallel()
{
	m_pCamera->SetParallel();
}

void cMain::SetPerspective()
{
	m_pCamera->SetPerspective();
}

void cMain::AddFigure(int n)
{
	m_nFigureNum = n;
}

void cMain::SetWire()
{
	if(m_pCurrentFigure)
		m_pCurrentFigure->SetWire(true);
}

void cMain::SetSolid()
{
	if (m_pCurrentFigure)
		m_pCurrentFigure->SetWire(false);
}
void cMain::SetColor(jbMath::Vector3 vec)
{
	if (m_pCurrentFigure)
		m_pCurrentFigure->SetColor(vec);
}

void cMain::SetWireColor(jbMath::Vector3 vec)
{
	if (m_pCurrentFigure)
		m_pCurrentFigure->SetWireColor(vec);
}
