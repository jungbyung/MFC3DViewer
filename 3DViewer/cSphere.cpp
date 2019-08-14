#include "stdafx.h"
#include "cSphere.h"
#include "cLight.h"
#include "cCamera.h"
#include "cBoundbox.h"
#include "cPyramid.h"

cSphere::cSphere()
{
}


cSphere::~cSphere()
{
}

HRESULT cSphere::Init()
{
	int rh = 30;
	float r = 1.f;
	float du = 2 * PI / (rh - 1);
	float dv = PI / (rh - 1);

	for (int i = 0; i < rh; i++)
	{
		for (int j = 0; j < rh; j++)
		{
			float u = i * du;
			float v = j * dv;
			vertices.push_back(jbUtill::vertex(jbMath::Vector3(r*cos(u)*sin(v), r*cos(v), -r*sin(u)*sin(v)), jbMath::Vector3(1.0f, 0.5f, 0)));
		}
	}

	for (int i = 0; i < rh - 1; i++)
	{
		for (int j = 0; j < rh - 1; j++)
		{
			int a = i * rh + j;
			int b = i * rh + j + 1;
			int c = (i + 1) * rh + j;
			int d = (i + 1) * rh + j + 1;

			indices.push_back(c);
			indices.push_back(a);
			indices.push_back(b);

			indices.push_back(c);
			indices.push_back(b);
			indices.push_back(d);
		}
	}

	m_pBoundbox = new cBoundbox;
	m_pBoundbox->SetAABB(vertices);

	m_pPyramid = new cPyramid;
	m_pPyramid->init(jbMath::Vector3(0, 0, 0));
	return S_OK;
}

void cSphere::update()
{
	cFigure::update();
	m_pBoundbox->update(world);
}

void cSphere::release()
{
}
/*
void cSphere::draw(CDC* pDC, cCamera pCamera, jbMath::Matrix vp, cLight* light)
{
	jbMath::Matrix matWVP = world * pCamera.GetViewProj();
	CArray<CPoint, CPoint> arrP;
	for (int i = 0; i < indices.size(); i += 3)
	{
		jbMath::Vector3 v1 = vertices[indices[i + 0]].pos;
		jbMath::Vector3 v2 = vertices[indices[i + 1]].pos;
		jbMath::Vector3 v3 = vertices[indices[i + 2]].pos;

		jbMath::Vector3 nor = jbUtill::ComputeNormal(v1.TransformCoord(&world), v2.TransformCoord(&world), v3.TransformCoord(&world));

		v1 = v1.TransformCoord(&matWVP);
		v2 = v2.TransformCoord(&matWVP);
		v3 = v3.TransformCoord(&matWVP);

		jbMath::Vector3 v12 = v2 - v1;
		jbMath::Vector3 v13 = v3 - v1;
		jbMath::Vector3 n = jbMath::Vector3::cross(v12, v13);

		if (jbMath::Vector3::Dot(jbMath::Vector3(0, 0, 1), n) >= 0) continue;
		// 색연산 -------------
		float f = jbMath::Vector3::Dot(jbMath::Vector3(0, 0, 1), nor);
		f = jbMath::Clamp(f, 1, 0);
		jbMath::Vector3 finalColor = vertices[indices[i]].color * f * 255;
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

void cSphere::SelectDraw(CDC* pDC, cCamera pCamera, jbMath::Matrix vp, cLight* light)
{
//	m_pBoundbox->draw(pDC, pCamera, vp);
	jbMath::Matrix matWVP = world * pCamera.GetViewProj();
	CArray<CPoint, CPoint> arrP;
	for (int i = 0; i < indices.size(); i += 3)
	{
		jbMath::Vector3 v1 = vertices[indices[i + 0]].pos;
		jbMath::Vector3 v2 = vertices[indices[i + 1]].pos;
		jbMath::Vector3 v3 = vertices[indices[i + 2]].pos;

		jbMath::Vector3 nor = jbUtill::ComputeNormal(v1.TransformCoord(&world), v2.TransformCoord(&world), v3.TransformCoord(&world));

		v1 = v1.TransformCoord(&matWVP);
		v2 = v2.TransformCoord(&matWVP);
		v3 = v3.TransformCoord(&matWVP);

		jbMath::Vector3 v12 = v2 - v1;
		jbMath::Vector3 v13 = v3 - v1;
		jbMath::Vector3 n = jbMath::Vector3::cross(v12, v13);

		if (jbMath::Vector3::Dot(jbMath::Vector3(0, 0, 1), n) >= 0) continue;
		// 색연산 -------------
		float f = jbMath::Vector3::Dot(jbMath::Vector3(0, 0, 1), nor);
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
*/