#include "stdafx.h"
#include "cPyramid.h"
#include "cCamera.h"

cPyramid::cPyramid()
{
}


cPyramid::~cPyramid()
{
}

void cPyramid::init(jbMath::Vector3 center)
{
	//x
	vertices.push_back(jbMath::Vector3(center.x, center.y + 0.25f, center.z));
	vertices.push_back(jbMath::Vector3(center.x, center.y - 0.25f, center.z));
	vertices.push_back(jbMath::Vector3(center.x + 0.5f, center.y + 0.125f, center.z));
	vertices.push_back(jbMath::Vector3(center.x + 0.5f, center.y - 0.125f, center.z));
	vertices.push_back(jbMath::Vector3(center.x + 0.75f, center.y, center.z));

	indices.push_back(0); indices.push_back(1); indices.push_back(2);
	indices.push_back(1); indices.push_back(2); indices.push_back(3);
	indices.push_back(3); indices.push_back(2); indices.push_back(4);
	//X

	//Y
	vertices.push_back(jbMath::Vector3(center.x - 0.25f, center.y, center.z));
	vertices.push_back(jbMath::Vector3(center.x + 0.25f, center.y, center.z));
	vertices.push_back(jbMath::Vector3(center.x + 0.125f, center.y + 0.5f, center.z));
	vertices.push_back(jbMath::Vector3(center.x - 0.125f, center.y + 0.5f, center.z));
	vertices.push_back(jbMath::Vector3(center.x, center.y + 0.75f, center.z));

	indices.push_back(5); indices.push_back(8); indices.push_back(7);
	indices.push_back(5); indices.push_back(7); indices.push_back(6);
	indices.push_back(8); indices.push_back(9); indices.push_back(7);
	//Y

	//Z
	vertices.push_back(jbMath::Vector3(center.x, center.y + 0.25f, center.z));
	vertices.push_back(jbMath::Vector3(center.x, center.y - 0.25f, center.z));
	vertices.push_back(jbMath::Vector3(center.x, center.y + 0.125f, center.z + 0.5f));
	vertices.push_back(jbMath::Vector3(center.x, center.y - 0.125f, center.z + 0.5f));
	vertices.push_back(jbMath::Vector3(center.x, center.y, center.z + 0.75f));

	indices.push_back(11); indices.push_back(10); indices.push_back(12);
	indices.push_back(11); indices.push_back(12); indices.push_back(13);
	indices.push_back(13); indices.push_back(12); indices.push_back(14);
	//Z

}

void cPyramid::draw(CDC * pDC, cCamera pCamera, jbMath::Matrix vp, jbMath::Matrix mat)
{
	jbMath::Matrix matWVP = mat * pCamera.GetViewProj();
	CArray<CPoint, CPoint> arrP;
	for (int i = 0; i < indices.size(); i += 3)
	{
		jbMath::Vector3 v1 = vertices[indices[i + 0]];
		jbMath::Vector3 v2 = vertices[indices[i + 1]];
		jbMath::Vector3 v3 = vertices[indices[i + 2]];

		v1 = v1.TransformCoord(&matWVP);
		v2 = v2.TransformCoord(&matWVP);
		v3 = v3.TransformCoord(&matWVP);

		jbMath::Vector3 v12 = v2 - v1;
		jbMath::Vector3 v13 = v3 - v1;
		jbMath::Vector3 n = jbMath::Vector3::cross(v12, v13).Normalize();

	//	if (jbMath::Vector3::Dot(jbMath::Vector3(0, 0, 1), n) >= 0) continue;

		v1 = v1.TransformCoord(&vp);
		v2 = v2.TransformCoord(&vp);
		v3 = v3.TransformCoord(&vp);

		arrP.Add(CPoint(v1.x, v1.y));
		arrP.Add(CPoint(v2.x, v2.y));
		arrP.Add(CPoint(v3.x, v3.y));

		pDC->Polygon(&arrP[0], arrP.GetCount());
		arrP.RemoveAll();
	}
}
