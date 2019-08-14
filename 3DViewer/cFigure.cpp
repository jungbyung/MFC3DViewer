#include "stdafx.h"
#include "cFigure.h"
#include "cBoundbox.h"
#include "cCamera.h"
#include "cPyramid.h"
#include "cLight.h"

cFigure::cFigure()
	: world(jbMath::Matrix::Identity())
	, scale(jbMath::Vector3(1, 1, 1))
	, isWire(false)
	, m_pBoundbox(nullptr)
	, m_pPyramid(nullptr)
	, color(jbMath::Vector3(255, 128, 0))
	, wireColor(jbMath::Vector3(0, 0, 0))
{
}


cFigure::~cFigure()
{
}

void cFigure::update()
{
	//jbUtill::ComputeNormal(&vertices, &indices, world);
}

void cFigure::draw(CDC * pDC, cCamera pCamera, jbMath::Matrix vp, cLight * light)
{
	auto matWVP = world * pCamera.GetViewProj();
	CArray<CPoint, CPoint> arrP;
	for (int i = 0; i < indices.size(); i += 3)
	{
		auto v1 = vertices[indices[i + 0]].pos;
		auto v2 = vertices[indices[i + 1]].pos;
		auto v3 = vertices[indices[i + 2]].pos;

		auto nor = jbUtill::ComputeNormal(v1, v2, v3);

		nor = nor.TransformNormal(&world).Normalize();

		v1 = v1.TransformCoord(&matWVP);
		v2 = v2.TransformCoord(&matWVP);
		v3 = v3.TransformCoord(&matWVP);

		auto v12 = v2 - v1;
		auto v13 = v3 - v1;
		auto n = jbMath::Vector3::cross(v12, v13);

		if (jbMath::Vector3::Dot(jbMath::Vector3(0, 0, 1), n) >= 0) continue;
		// 색연산 -------------
		auto f = jbMath::Vector3::Dot(-light->GetDir(), nor);
		f = jbMath::Clamp(f, 1, 0);
		auto finalColor = color * f;
		auto finalwire = wireColor * f;
		//------------
		CPen pen;
		pen.CreatePen(PS_SOLID, 1, jbUtill::GetRGB(finalwire));
		auto oldPen = pDC->SelectObject(&pen);
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

void cFigure::SelectDraw(CDC * pDC, cCamera pCamera, jbMath::Matrix vp, cLight * light)
{
	//if(m_pBoundbox)
	//	m_pBoundbox->draw(pDC, pCamera, vp);
	auto matWVP = world * pCamera.GetViewProj();
	CArray<CPoint, CPoint> arrP;
	for (int i = 0; i < indices.size(); i += 3)
	{
		auto v1 = vertices[indices[i + 0]].pos;
		auto v2 = vertices[indices[i + 1]].pos;
		auto v3 = vertices[indices[i + 2]].pos;

		auto nor = jbUtill::ComputeNormal(v1, v2, v3);

		nor = nor.TransformNormal(&world).Normalize();

		v1 = v1.TransformCoord(&world);
		v2 = v2.TransformCoord(&world);
		v3 = v3.TransformCoord(&world);

		v1 = v1.TransformCoord(&pCamera.GetViewProj());
		v2 = v2.TransformCoord(&pCamera.GetViewProj());
		v3 = v3.TransformCoord(&pCamera.GetViewProj());

		auto v12 = v2 - v1;
		auto v13 = v3 - v1;
		auto n = jbMath::Vector3::cross(v12, v13);

		if (jbMath::Vector3::Dot(jbMath::Vector3(0,0,1), n) >= 0) continue;
		// 색연산 -------------
		auto f = jbMath::Vector3::Dot(-light->GetDir(), nor);
		f = jbMath::Clamp(f, 1, 0);
		auto finalColor = RGB(255,0,0) * f;
		//------------
		CPen pen;
		pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		auto oldPen = pDC->SelectObject(&pen);
		CBrush brush;
		CBrush* oldBrush;

		if (!isWire)
			brush.CreateSolidBrush(finalColor);
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
//	m_pPyramid->draw(pDC, pCamera, vp, world);
}

void cFigure::Moving()
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

	auto sc = jbMath::Scale(scale);
	auto rot = jbMath::RotateXYZ(angle);

	dir = dir.TransformNormal(&rot).Normalize();
	if (GetKeyState('W') & 0x8000)
	{
		pos = pos + (dir * 0.1f);
	}
	if (GetKeyState('S') & 0x8000)
	{
		pos = pos - (dir * 0.1f);
	}
	if (GetKeyState('A') & 0x8000)
	{
		dir = jbMath::Vector3::cross(jbMath::Vector3(0, 1, 0), dir);

		pos = pos - dir * 0.1f;
	}
	if (GetKeyState('D') & 0x8000)
	{
		dir = jbMath::Vector3::cross(jbMath::Vector3(0, 1, 0), dir);

		pos = pos + dir * 0.1f;
	}
	auto t = jbMath::Translation(&pos);
	world = sc * rot * t;
	forward = dir;
	right = jbMath::Vector3::cross(jbMath::Vector3(0, 1, 0), forward).Normalize();
	up = jbMath::Vector3::cross(forward, right).Normalize();
}

void cFigure::SetPosition(jbMath::Vector3 vec)
{
	pos = vec;
}

void cFigure::SetRotate(jbMath::Vector3 vec)
{
	angle = vec;
}

void cFigure::SetScale(jbMath::Vector3 vec)
{
	scale = vec;
}
