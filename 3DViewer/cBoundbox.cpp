#include "stdafx.h"
#include "cBoundbox.h"
#include "cCamera.h"

cBoundbox::cBoundbox()
{
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
}


cBoundbox::~cBoundbox()
{
}

void cBoundbox::SetAABB(std::vector<jbUtill::vertex> v)
{
	vertices.clear();
	vMax = v[0].pos;
	vMin = v[0].pos;

	for (UINT i = 0; i < v.size(); ++i)
	{
		jbMath::Vector3 vec = v[i].pos;
		vMax = jbMath::Vector3::vecMax(vMax, vec);
		vMin = jbMath::Vector3::vecMin(vMin, vec);
	}

	vertices.push_back(jbMath::Vector3(vMin.x, vMin.y, vMin.z));
	vertices.push_back(jbMath::Vector3(vMin.x, vMax.y, vMin.z));
	vertices.push_back(jbMath::Vector3(vMax.x, vMax.y, vMin.z));
	vertices.push_back(jbMath::Vector3(vMax.x, vMin.y, vMin.z));
	vertices.push_back(jbMath::Vector3(vMin.x, vMin.y, vMax.z));
	vertices.push_back(jbMath::Vector3(vMin.x, vMax.y, vMax.z));
	vertices.push_back(jbMath::Vector3(vMax.x, vMax.y, vMax.z));
	vertices.push_back(jbMath::Vector3(vMax.x, vMin.y, vMax.z));


}

void cBoundbox::SetAABB(std::vector<jbUtill::pcn> v)
{
	vertices.clear();
	vMax = v[0].pos;
	vMin = v[0].pos;

	for (UINT i = 0; i < v.size(); ++i)
	{
		jbMath::Vector3 vec = v[i].pos;
		vMax = jbMath::Vector3::vecMax(vMax, vec);
		vMin = jbMath::Vector3::vecMin(vMin, vec);
	}

	vertices.push_back(jbMath::Vector3(vMin.x, vMin.y, vMin.z));
	vertices.push_back(jbMath::Vector3(vMin.x, vMax.y, vMin.z));
	vertices.push_back(jbMath::Vector3(vMax.x, vMax.y, vMin.z));
	vertices.push_back(jbMath::Vector3(vMax.x, vMin.y, vMin.z));
	vertices.push_back(jbMath::Vector3(vMin.x, vMin.y, vMax.z));
	vertices.push_back(jbMath::Vector3(vMin.x, vMax.y, vMax.z));
	vertices.push_back(jbMath::Vector3(vMax.x, vMax.y, vMax.z));
	vertices.push_back(jbMath::Vector3(vMax.x, vMin.y, vMax.z));


}
void cBoundbox::SetOBB(std::vector<jbUtill::vertex> v)
{
}

void cBoundbox::SetBB(jbMath::Matrix mat)
{
	vertices[0] = jbMath::Vector3(vMin.x, vMin.y, vMin.z);
	vertices[1] = jbMath::Vector3(vMin.x, vMax.y, vMin.z);
	vertices[2] = jbMath::Vector3(vMax.x, vMax.y, vMin.z);
	vertices[3] = jbMath::Vector3(vMax.x, vMin.y, vMin.z);
	vertices[4] = jbMath::Vector3(vMin.x, vMin.y, vMax.z);
	vertices[5] = jbMath::Vector3(vMin.x, vMax.y, vMax.z);
	vertices[6] = jbMath::Vector3(vMax.x, vMax.y, vMax.z);
	vertices[7] = jbMath::Vector3(vMax.x, vMin.y, vMax.z);
	std::vector<jbMath::Vector3> v(vertices.size());

	//mat = jbMath::Scale(1.1, 1.1, 1.1) * mat;
	for (int i = 0; i < vertices.size(); ++i)
	{
		v[i] = vertices[i].TransformCoord(&mat);
	}
	min = v[0];
	max = v[0];

	for (UINT i = 0; i < v.size(); ++i)
	{
		jbMath::Vector3 vec = v[i];
		max = jbMath::Vector3::vecMax(max, vec);
		min = jbMath::Vector3::vecMin(min, vec);
	}
}

void cBoundbox::update(jbMath::Matrix mat)
{
	vertices[0] = jbMath::Vector3(vMin.x, vMin.y, vMin.z);
	vertices[1] = jbMath::Vector3(vMin.x, vMax.y, vMin.z);
	vertices[2] = jbMath::Vector3(vMax.x, vMax.y, vMin.z);
	vertices[3] = jbMath::Vector3(vMax.x, vMin.y, vMin.z);
	vertices[4] = jbMath::Vector3(vMin.x, vMin.y, vMax.z);
	vertices[5] = jbMath::Vector3(vMin.x, vMax.y, vMax.z);
	vertices[6] = jbMath::Vector3(vMax.x, vMax.y, vMax.z);
	vertices[7] = jbMath::Vector3(vMax.x, vMin.y, vMax.z);
	std::vector<jbMath::Vector3> v(vertices.size());

	mat = jbMath::Scale(1.1, 1.1, 1.1) * mat;
	for (int i = 0; i < vertices.size(); ++i)
	{
		v[i] = vertices[i].TransformCoord(&mat);
	}
	min = v[0];
	max = v[0];

	for (UINT i = 0; i < v.size(); ++i)
	{
		jbMath::Vector3 vec = v[i];
		max = jbMath::Vector3::vecMax(max, vec);
		min = jbMath::Vector3::vecMin(min, vec);
	}
	vertices[0] = jbMath::Vector3(min.x, min.y, min.z);
	vertices[1] = jbMath::Vector3(min.x, max.y, min.z);
	vertices[2] = jbMath::Vector3(max.x, max.y, min.z);
	vertices[3] = jbMath::Vector3(max.x, min.y, min.z);
	vertices[4] = jbMath::Vector3(min.x, min.y, max.z);
	vertices[5] = jbMath::Vector3(min.x, max.y, max.z);
	vertices[6] = jbMath::Vector3(max.x, max.y, max.z);
	vertices[7] = jbMath::Vector3(max.x, min.y, max.z);
}

void cBoundbox::draw(CDC * pDC, cCamera pCamera, jbMath::Matrix vp)
{
	jbMath::Matrix matWVP = pCamera.GetViewProj();
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
		jbMath::Vector3 n = jbMath::Vector3::cross(v12, v13);

		if (jbMath::Vector3::Dot(jbMath::Vector3(0, 0, 1), n) >= 0) continue;

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
