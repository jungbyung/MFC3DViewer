#include "stdafx.h"
#include "cMesh.h"
#include "cCamera.h"
#include "cLight.h"
#include "cBoundbox.h"

cMesh::cMesh()
	: world(jbMath::Matrix::Identity())
	, angle(jbMath::Vector3(0, 0, 0))
	, scale(jbMath::Vector3(1, 1, 1))
	, isWire(false)
{
}


cMesh::~cMesh()
{
}

void cMesh::init()
{
	m_pBoundbox = new cBoundbox;
	m_pBoundbox->SetAABB(vertices);
}

void cMesh::update()
{
	m_pBoundbox->update(world);
}

void cMesh::release()
{
}

void cMesh::draw(CDC * pDC, cCamera pCamera, jbMath::Matrix vp, cLight * light)
{
//	m_pBoundbox->draw(pDC, pCamera, vp);
	jbMath::Matrix matWVP = world * pCamera.GetViewProj();
	CArray<CPoint, CPoint> arrP;
	for (int i = 0; i < indices.size(); i += 3)
	{
		jbMath::Vector3 v1 = vertices[indices[i + 0]].pos;
		jbMath::Vector3 v2 = vertices[indices[i + 1]].pos;
		jbMath::Vector3 v3 = vertices[indices[i + 2]].pos;

		jbMath::Vector3 nor = vertices[indices[i]].normal;

		nor = nor.TransformNormal(&world).Normalize();

		v1 = v1.TransformCoord(&matWVP);
		v2 = v2.TransformCoord(&matWVP);
		v3 = v3.TransformCoord(&matWVP);

		jbMath::Vector3 v12 = v2 - v1;
		jbMath::Vector3 v13 = v3 - v1;
		jbMath::Vector3 n = jbMath::Vector3::cross(v12, v13);

		if (jbMath::Vector3::Dot(jbMath::Vector3(0, 0, -1), n) >= 0) continue;
		// 색연산 -------------
		float f = jbMath::Vector3::Dot(-light->GetDir(), nor);
		f = jbMath::Clamp(f, 1, 0);
		jbMath::Vector3 finalColor = jbMath::Vector3(1, 0.5, 0) * f * 255;
		COLOR16 c = jbUtill::GetRGB(finalColor);
		//------------
		CPen pen;
		pen.CreatePen(PS_SOLID, 1, RGB(25.5, 25.5, 25.5));
		CPen* oldPen = pDC->SelectObject(&pen);
		CBrush brush;
		CBrush* oldBrush;

		brush.CreateSolidBrush(jbUtill::GetRGB(finalColor));
		oldBrush = pDC->SelectObject(&brush);


		v1 = v1.TransformCoord(&vp);
		v2 = v2.TransformCoord(&vp);
		v3 = v3.TransformCoord(&vp);

		arrP.Add(CPoint(v1.x, v1.y));
		arrP.Add(CPoint(v2.x, v2.y));
		arrP.Add(CPoint(v3.x, v3.y));

		pDC->Polygon(&arrP[0], arrP.GetCount());
		arrP.RemoveAll();
		pDC->SelectObject(oldBrush);
		pDC->SelectObject(oldPen);
	}
}

void cMesh::SelectDraw(CDC * pDC, cCamera pCamera, jbMath::Matrix vp, cLight * light)
{
//	m_pBoundbox->draw(pDC, pCamera, vp);
	jbMath::Matrix matWVP = world * pCamera.GetViewProj();
	CArray<CPoint, CPoint> arrP;
	for (int i = 0; i < indices.size(); i += 3)
	{
		jbMath::Vector3 v1 = vertices[indices[i + 0]].pos;
		jbMath::Vector3 v2 = vertices[indices[i + 1]].pos;
		jbMath::Vector3 v3 = vertices[indices[i + 2]].pos;

		jbMath::Vector3 nor = vertices[indices[i]].normal;

		nor = nor.TransformNormal(&world).Normalize();

		v1 = v1.TransformCoord(&world);
		v2 = v2.TransformCoord(&world);
		v3 = v3.TransformCoord(&world);

		v1 = v1.TransformCoord(&pCamera.GetViewProj());
		v2 = v2.TransformCoord(&pCamera.GetViewProj());
		v3 = v3.TransformCoord(&pCamera.GetViewProj());

		jbMath::Vector3 v12 = v2 - v1;
		jbMath::Vector3 v13 = v3 - v1;
		jbMath::Vector3 n = jbMath::Vector3::cross(v12, v13);

		if (jbMath::Vector3::Dot(jbMath::Vector3(0, 0, -1), n) >= 0) continue;
		// 색연산 -------------
		float f = jbMath::Vector3::Dot(-light->GetDir(), nor);
		f = jbMath::Clamp(f, 1, 0);
		jbMath::Vector3 finalColor = jbMath::Vector3(1, 0, 0) * f * 255;
		COLOR16 c = jbUtill::GetRGB(finalColor);
		//------------
		CPen pen;
		pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* oldPen = pDC->SelectObject(&pen);
		CBrush brush;
		CBrush* oldBrush;

		if (!isWire)
			brush.CreateSolidBrush(jbUtill::GetRGB(finalColor));
		oldBrush = pDC->SelectObject(&brush);

		v1 = v1.TransformCoord(&vp);
		v2 = v2.TransformCoord(&vp);
		v3 = v3.TransformCoord(&vp);

		arrP.Add(CPoint(v1.x, v1.y));
		arrP.Add(CPoint(v2.x, v2.y));
		arrP.Add(CPoint(v3.x, v3.y));

		pDC->Polygon(&arrP[0], arrP.GetCount());
		arrP.RemoveAll();
		pDC->SelectObject(oldBrush);
		pDC->SelectObject(oldPen);
	}
}

void cMesh::Moving()
{
	jbMath::Vector3 dir(0, 0, 1.f);

	if (GetKeyState(VK_F1) & 0x8000)
	{
		angle.SetVector3(0, 0, 0);
		pos.SetVector3(0, 0, 0);
		scale.SetVector3(1, 1, 1);
	}

	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		angle.SetY(angle.y - 0.1f);
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		angle.SetY(angle.y + 0.1f);
	}
	if (GetKeyState(VK_UP) & 0x8000)
	{
		angle.SetX(angle.x - 0.1f);
	}
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		angle.SetX(angle.x + 0.1f);
	}

	if (GetKeyState(VK_NUMPAD1) & 0x8000)
	{
		scale.SetX(scale.x + 0.1f);
	}
	if (GetKeyState(VK_NUMPAD2) & 0x8000)
	{
		scale.SetY(scale.y + 0.1f);
	}
	if (GetKeyState(VK_NUMPAD3) & 0x8000)
	{
		scale.SetZ(scale.z + 0.1f);
	}
	if (GetKeyState(VK_NUMPAD4) & 0x8000)
	{
		scale.SetX(scale.x - 0.1f);
	}
	if (GetKeyState(VK_NUMPAD5) & 0x8000)
	{
		scale.SetY(scale.y - 0.1f);
	}
	if (GetKeyState(VK_NUMPAD6) & 0x8000)
	{
		scale.SetZ(scale.z - 0.1f);
	}

	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		scale.SetVector3(1, 1, 1);
	}

	jbMath::Matrix sc = jbMath::Scale(scale);
	jbMath::Matrix rot = jbMath::RotateXYZ(angle);

	dir = dir.TransformNormal(&rot).Normalize();
	if (GetKeyState('W') & 0x8000)
	{
		pos = pos - (dir * 0.1f);
	}
	if (GetKeyState('S') & 0x8000)
	{
		pos = pos + (dir * 0.1f);
	}
	if (GetKeyState('A') & 0x8000)
	{
		dir = jbMath::Vector3::cross(jbMath::Vector3(0, 1, 0), dir);

		pos = pos + dir * 0.1f;
	}
	if (GetKeyState('D') & 0x8000)
	{
		dir = jbMath::Vector3::cross(jbMath::Vector3(0, 1, 0), dir);

		pos = pos - dir * 0.1f;
	}
	jbMath::Matrix t = jbMath::Translation(&pos);
	world = sc * rot * t;
}

void cMesh::SetPosition(jbMath::Vector3 vec)
{
	pos = vec;
}

void cMesh::SetRotate(jbMath::Vector3 vec)
{
	angle = vec;
}

void cMesh::SetScale(jbMath::Vector3 vec)
{
	scale = vec;
}
