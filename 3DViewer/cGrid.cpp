#include "stdafx.h"
#include "cGrid.h"
#include "cCamera.h"

cGrid::cGrid()
	: n(10)
	, f(1.f)
{
}


cGrid::~cGrid()
{
}
void cGrid::Setup()
{
	float fmx = n * f;
	for (int i = 1; i <= n; ++i)
	{
		line.push_back(jbMath::Vector3(-fmx, 0, -i * f));
		line.push_back(jbMath::Vector3(fmx, 0, -i * f));
		line.push_back(jbMath::Vector3(-fmx, 0, i * f));
		line.push_back(jbMath::Vector3(fmx, 0, i * f));


		line.push_back(jbMath::Vector3(-i*f, 0, -fmx));
		line.push_back(jbMath::Vector3(-i*f, 0, fmx));
		line.push_back(jbMath::Vector3(i*f, 0, -fmx));
		line.push_back(jbMath::Vector3(i*f, 0, fmx));
	}

	line.push_back(jbMath::Vector3(-fmx, 0, 0));
	line.push_back(jbMath::Vector3(fmx, 0, 0));

	line.push_back(jbMath::Vector3(0, 0, -fmx));
	line.push_back(jbMath::Vector3(0, 0, fmx));

	
}

void cGrid::draw(CDC * pDC, cCamera pCamera, jbMath::Matrix vp)
{
	for (int i = 0; i < line.size(); i += 2)
	{
		jbMath::Vector3 v1 = line[i];
		jbMath::Vector3 v2 = line[i+1];

		v1 = v1.TransformCoord(&(pCamera.GetViewProj() * vp));
		v2 = v2.TransformCoord(&(pCamera.GetViewProj() * vp));

		pDC->MoveTo(v1.x, v1.y);
		pDC->LineTo(v2.x, v2.y);
	}
	jbMath::Vector3 vx = jbMath::Vector3(n*f, 0, 0);
	jbMath::Vector3 vz = jbMath::Vector3(0, 0, n*f);

	vx = vx.TransformCoord(&(pCamera.GetViewProj() * vp));
	vz = vz.TransformCoord(&(pCamera.GetViewProj() * vp));

	pDC->TextOutA(vx.x, vx.y, "X");
	pDC->TextOutA(vz.x, vz.y, "Z");


}
