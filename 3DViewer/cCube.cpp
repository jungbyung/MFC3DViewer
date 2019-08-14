#include "stdafx.h"
#include "cCube.h"
#include "cLight.h"
#include <algorithm>
#include "cCamera.h"
#include "cBoundbox.h"
#include "cPyramid.h"

cCube::cCube()
{
}


cCube::~cCube()
{
}

HRESULT cCube::Init()
{
	float r = 0.5f;

	//vertices.push_back(jbUtill::vertex(jbMath::Vector3(-r, -r,  r), jbMath::Vector3(1,0.5f,0))); // 0
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3(-r,  r,  r), jbMath::Vector3(1,0.5f,0))); // 1
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3( r,  r,  r), jbMath::Vector3(1,0.5f,0))); // 2
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3(-r, -r,  r), jbMath::Vector3(1,0.5f,0))); // 0
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3( r,  r,  r), jbMath::Vector3(1,0.5f,0))); // 2
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3( r, -r,  r), jbMath::Vector3(1,0.5f,0))); // 3
	//															    
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3(-r, -r, -r), jbMath::Vector3(1,0.5f,0))); // 4
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3( r,  r, -r), jbMath::Vector3(1,0.5f,0))); // 6
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3(-r,  r, -r), jbMath::Vector3(1,0.5f,0))); // 5
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3(-r, -r, -r), jbMath::Vector3(1,0.5f,0))); // 4
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3( r, -r, -r), jbMath::Vector3(1,0.5f,0))); // 7
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3( r,  r, -r), jbMath::Vector3(1,0.5f,0))); // 6
	//															    
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3(-r, -r, -r), jbMath::Vector3(1,0.5f,0))); // 4
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3(-r,  r, -r), jbMath::Vector3(1,0.5f,0))); // 5
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3(-r,  r,  r), jbMath::Vector3(1,0.5f,0))); // 1
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3(-r, -r, -r), jbMath::Vector3(1,0.5f,0))); // 4
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3(-r,  r,  r), jbMath::Vector3(1,0.5f,0))); // 1
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3(-r, -r,  r), jbMath::Vector3(1,0.5f,0))); // 0
	//				   											    
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3( r, -r,  r), jbMath::Vector3(1,0.5f,0))); // 3
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3( r,  r,  r), jbMath::Vector3(1,0.5f,0))); // 2
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3( r,  r, -r), jbMath::Vector3(1,0.5f,0))); // 6
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3( r, -r,  r), jbMath::Vector3(1,0.5f,0))); // 3
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3( r,  r, -r), jbMath::Vector3(1,0.5f,0))); // 6
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3( r, -r, -r), jbMath::Vector3(1,0.5f,0))); // 7
	//				   											    
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3(-r,  r,  r), jbMath::Vector3(1,0.5f,0))); // 1
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3(-r,  r, -r), jbMath::Vector3(1,0.5f,0))); // 5
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3( r,  r, -r), jbMath::Vector3(1,0.5f,0))); // 6
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3(-r,  r,  r), jbMath::Vector3(1,0.5f,0))); // 1
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3( r,  r, -r), jbMath::Vector3(1,0.5f,0))); // 6
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3( r,  r,  r), jbMath::Vector3(1,0.5f,0))); // 2
	//				   											    
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3(-r, -r, -r), jbMath::Vector3(1,0.5f,0))); // 4
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3(-r, -r,  r), jbMath::Vector3(1,0.5f,0))); // 0
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3( r, -r,  r), jbMath::Vector3(1,0.5f,0))); // 3
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3(-r, -r, -r), jbMath::Vector3(1,0.5f,0))); // 4
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3( r, -r,  r), jbMath::Vector3(1,0.5f,0))); // 3
	//vertices.push_back(jbUtill::vertex(jbMath::Vector3( r, -r, -r), jbMath::Vector3(1,0.5f,0))); // 7
	//
	//for (int i = 0; i < 36; i++) indices.push_back(i);
	vertices.push_back(jbUtill::vertex(jbMath::Vector3(-r, -r, -r), jbMath::Vector3(1, 0.5f, 0))); // 0
	vertices.push_back(jbUtill::vertex(jbMath::Vector3(-r,  r, -r), jbMath::Vector3(1, 0.5f, 0))); // 1
	vertices.push_back(jbUtill::vertex(jbMath::Vector3( r,  r, -r), jbMath::Vector3(1, 0.5f, 0))); // 2
	vertices.push_back(jbUtill::vertex(jbMath::Vector3( r, -r, -r), jbMath::Vector3(1, 0.5f, 0))); // 3
	vertices.push_back(jbUtill::vertex(jbMath::Vector3(-r, -r,  r), jbMath::Vector3(1, 0.5f, 0))); // 4
	vertices.push_back(jbUtill::vertex(jbMath::Vector3(-r,  r,  r), jbMath::Vector3(1, 0.5f, 0))); // 5
	vertices.push_back(jbUtill::vertex(jbMath::Vector3( r,  r,  r), jbMath::Vector3(1, 0.5f, 0))); // 6
	vertices.push_back(jbUtill::vertex(jbMath::Vector3( r, -r,  r), jbMath::Vector3(1, 0.5f, 0))); // 7

	indices.push_back(0); indices.push_back(1); indices.push_back(2);
	indices.push_back(0); indices.push_back(2); indices.push_back(3);
	
	indices.push_back(4); indices.push_back(6); indices.push_back(5);
	indices.push_back(4); indices.push_back(7); indices.push_back(6);
	
	indices.push_back(4); indices.push_back(5); indices.push_back(1);
	indices.push_back(4); indices.push_back(1); indices.push_back(0);
	
	indices.push_back(3); indices.push_back(2); indices.push_back(6);
	indices.push_back(3); indices.push_back(6); indices.push_back(7);
	
	indices.push_back(1); indices.push_back(5); indices.push_back(6);
	indices.push_back(1); indices.push_back(6); indices.push_back(2);
	
	indices.push_back(4); indices.push_back(0); indices.push_back(3);
	indices.push_back(4); indices.push_back(3); indices.push_back(7);

	m_pBoundbox = new cBoundbox;
	m_pBoundbox->SetAABB(vertices);

	m_pPyramid = new cPyramid;
	m_pPyramid->init(jbMath::Vector3(0, 0, 0));

	return S_OK;
}
void cCube::update()
{
	cFigure::update();
	m_pBoundbox->update(world);
}

void cCube::release()
{
}
/*
void cCube::draw(CDC* pDC, cCamera pCamera, jbMath::Matrix vp, cLight* light)
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
		pen.CreatePen(PS_SOLID, 1, RGB(0,0,0));
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

void cCube::SelectDraw(CDC* pDC, cCamera pCamera, jbMath::Matrix vp, cLight* light)
{
	m_pBoundbox->draw(pDC, pCamera, vp);
	jbMath::Matrix matWVP = world * pCamera.GetViewProj();
	CArray<CPoint, CPoint> arrP;
	for (int i = 0; i < indices.size(); i += 3)
	{
		jbMath::Vector3 v1 = vertices[indices[i + 0]].pos;
		jbMath::Vector3 v2 = vertices[indices[i + 1]].pos;
		jbMath::Vector3 v3 = vertices[indices[i + 2]].pos;
		//jbMath::Vector3 v4 = vertices[indices[i + 5]].pos;

		jbMath::Vector3 nor = jbUtill::ComputeNormal(v1.TransformCoord(&world), v2.TransformCoord(&world), v3.TransformCoord(&world));
		//nor = nor.TransformNormal(&pCamera.GetViewProj()).Normalize();
		v1 = v1.TransformCoord(&matWVP);
		v2 = v2.TransformCoord(&matWVP);
		v3 = v3.TransformCoord(&matWVP);
		//v4 = v4.TransformCoord(&matWVP);

		jbMath::Vector3 v12 = v2 - v1;
		jbMath::Vector3 v13 = v3 - v1;
		jbMath::Vector3 n = jbMath::Vector3::cross(v12, v13).Normalize();

		float d = jbMath::Vector3::Dot(jbMath::Vector3(0,0,1), n);
		if (d >= 0)
			continue;
		//// 색연산 -------------
		float f = jbMath::Vector3::Dot(-jbMath::Vector3(0, 0, -1), nor);
		f = jbMath::Clamp(f, 1, 0);
		jbMath::Vector3 finalColor = jbMath::Vector3(1,0,0) * f * 255;
		COLOR16 c = jbUtill::GetRGB(finalColor);
		//------------
		CPen pen;
		pen.CreatePen(PS_SOLID, 1, RGB(0,0,0));
		CPen* oldPen = pDC->SelectObject(&pen);
		CBrush brush;
		CBrush* oldBrush;
		
		if (!isWire)
			brush.CreateSolidBrush(jbUtill::GetRGB(finalColor));
		oldBrush = pDC->SelectObject(&brush);

	//	CDC memdc;
	//	BITMAP bmpInfo;
	//	memdc.CreateCompatibleDC(pDC);
	//
	//	CBitmap bmp;
	//	CBitmap* pOldBmp = nullptr;
	//
	//	bmp.LoadBitmapW(IDB_BITMAP1);
	//	bmp.GetBitmap(&bmpInfo);
	//	pOldBmp = memdc.SelectObject(&bmp);

		v1 = v1.TransformCoord(&vp);
		v2 = v2.TransformCoord(&vp);
		v3 = v3.TransformCoord(&vp);
		//v4 = v4.TransformCoord(&vp);

		arrP.Add(CPoint(v1.x, v1.y));
		arrP.Add(CPoint(v2.x, v2.y));
		arrP.Add(CPoint(v3.x, v3.y));
		//arrP.Add(CPoint(v4.x, v4.y));

//		pDC->StretchBlt(v2.x, v2.y, abs(v2.x - v3.x), abs(v1.y - v2.y), &memdc, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
		//memdc.SelectObject(pOldBmp);

		pDC->Polygon(&arrP[0], arrP.GetCount());
		arrP.RemoveAll();
		pDC->SelectObject(oldBrush);
		pDC->SelectObject(oldPen);
	}
}
*/