#include "stdafx.h"
#include "Utill.h"
#include "cCamera.h"
#include "cFigure.h"
#include "cBoundbox.h"
#include "cPyramid.h"
#include "cMesh.h"
#include "cCamera.h"

namespace jbUtill
{
	jbMath::Vector3 ComputeNormal(jbMath::Vector3 p0, jbMath::Vector3 p1, jbMath::Vector3 p2)
	{
		jbMath::Vector3 vec;

		jbMath::Vector3 v1 = p1 - p0;
		jbMath::Vector3 v2 = p2 - p0;
		vec = jbMath::Vector3::cross(v1, v2).Normalize();

		return vec;

	}
	DWORD GetRGB(jbMath::Vector3 vec)
	{
		return RGB(vec.x, vec.y, vec.z);
	}
	BOOL ComputeRayCast(Ray ray, cFigure * fig)
	{
		for (int i = 0; i < fig->GetIndices().size(); i+=3)
		{
			//정점3개
			jbMath::Vector3 p0 = fig->GetVertices()[fig->GetIndices()[i]].pos.TransformCoord(&fig->GetWorld());
			jbMath::Vector3 p1 = fig->GetVertices()[fig->GetIndices()[i+1]].pos.TransformCoord(&fig->GetWorld());
			jbMath::Vector3 p2 = fig->GetVertices()[fig->GetIndices()[i+2]].pos.TransformCoord(&fig->GetWorld());

			jbMath::Vector3 pvec = jbMath::Vector3::cross(ray.dir, p2 - p0);
			float f = jbMath::Vector3::Dot(p1 - p0, pvec);

			jbMath::Vector3 tvec;
			if (f > 0) tvec = ray.ori - p0;
			else
			{
				tvec = p0 - ray.ori;
				f = -f;
			}
			if (f < EPSILON) continue;

			float u = jbMath::Vector3::Dot(tvec, pvec);
			if (u < 0.f || u > f) continue;

			jbMath::Vector3 qvec;
			qvec = jbMath::Vector3::cross(tvec, p1 - p0);
			float v = jbMath::Vector3::Dot(ray.dir, qvec);
			if (v <0.f || u + v > f) continue;

			return true;
		}
		return false;
	}
	BOOL ComputeRayCast(Ray ray, cMesh * pMesh)
	{
		for (int i = 0; i < pMesh->GetBondbox()->GetIndices().size(); i += 3)
		{
			//정점3개
			jbMath::Vector3 p0 = pMesh->GetBondbox()->GetVertices()[pMesh->GetBondbox()->GetIndices()[i]].TransformCoord(&pMesh->GetWorld());
			jbMath::Vector3 p1 = pMesh->GetBondbox()->GetVertices()[pMesh->GetBondbox()->GetIndices()[i + 1]].TransformCoord(&pMesh->GetWorld());
			jbMath::Vector3 p2 = pMesh->GetBondbox()->GetVertices()[pMesh->GetBondbox()->GetIndices()[i + 2]].TransformCoord(&pMesh->GetWorld());

			jbMath::Vector3 pvec = jbMath::Vector3::cross(ray.dir, p2 - p0);
			float f = jbMath::Vector3::Dot(p1 - p0, pvec);

			jbMath::Vector3 tvec;
			if (f > 0) tvec = ray.ori - p0;
			else
			{
				tvec = p0 - ray.ori;
				f = -f;
			}
			if (f < EPSILON) continue;

			float u = jbMath::Vector3::Dot(tvec, pvec);
			if (u < 0.f || u > f) continue;

			jbMath::Vector3 qvec;
			qvec = jbMath::Vector3::cross(tvec, p1 - p0);
		//	qvec = qvec.Normalize();
			float v = jbMath::Vector3::Dot(ray.dir, qvec);
			if (v <0.f || u + v > f) continue;

			return true;
		}
		return false;
	}
	BOOL ComputeRayCast(Ray ray, cPyramid * fig, int& n, jbMath::Matrix parent)
	{
		n = -1;
		for (int i = 0; i < fig->GetIndices().size(); i += 3)
		{
			//정점3개
			jbMath::Vector3 p0 = fig->GetVertices()[fig->GetIndices()[i]].TransformCoord(&parent);
			jbMath::Vector3 p1 = fig->GetVertices()[fig->GetIndices()[i + 1]].TransformCoord(&parent);
			jbMath::Vector3 p2 = fig->GetVertices()[fig->GetIndices()[i + 2]].TransformCoord(&parent);

			jbMath::Vector3 pvec = jbMath::Vector3::cross(ray.dir, p2 - p0);
			float f = jbMath::Vector3::Dot(p1 - p0, pvec);

			jbMath::Vector3 tvec;
			if (f > 0) tvec = ray.ori - p0;
			else
			{
				tvec = p0 - ray.ori;
				f = -f;
			}
			if (f < EPSILON) continue;

			float u = jbMath::Vector3::Dot(tvec, pvec);
			if (u < 0.f || u > f) continue;

			jbMath::Vector3 qvec;
			qvec = jbMath::Vector3::cross(tvec, p1 - p0);
			float v = jbMath::Vector3::Dot(ray.dir, qvec);
			if (v <0.f || u + v > f) continue;

			n = i;

			return true;
		}
		return false;
	}
	BOOL AABBCollision(cBoundbox * A, cBoundbox * B)
	{
		jbMath::Vector3 aMax = A->max;
		jbMath::Vector3 aMin = A->min;

		jbMath::Vector3 bMax = B->max;
		jbMath::Vector3 bMin = B->min;

		jbMath::Vector3 aRadius = (aMax - aMin) * 0.5f;
		jbMath::Vector3 bRadius = (bMax - bMin) * 0.5f;

		jbMath::Vector3 aCenter = (aMax + aMin) * 0.5f;
		jbMath::Vector3 bCenter = (bMax + bMin) * 0.5f;

		if (fabs(aCenter.x - bCenter.x) <= aRadius.x + bRadius.x &&
			fabs(aCenter.y - bCenter.y) <= aRadius.y + bRadius.y &&
			fabs(aCenter.z - bCenter.z) <= aRadius.z + bRadius.z)
			return TRUE;

		return FALSE;

	}
	BOOL OBBCollision(cFigure * a, cFigure * b)
	{

		struct OBB
		{
			jbMath::Vector3 center;
			jbMath::Vector3 axis[3];
			float length[3];
		};

		a->GetBondbox()->SetBB(a->GetWorld());
		b->GetBondbox()->SetBB(b->GetWorld());

		OBB obbA, obbB;

		obbA.center = a->GetBondbox()->GetCenter();
		obbA.axis[0] = a->GetRight();
		obbA.axis[1] = a->GetUp();
		obbA.axis[2] = a->GetForward();

		obbA.length[0] = fabs(a->GetBondbox()->GetExtents().x * a->GetScale().x);
		obbA.length[1] = fabs(a->GetBondbox()->GetExtents().y * a->GetScale().y);
		obbA.length[2] = fabs(a->GetBondbox()->GetExtents().z * a->GetScale().z);

		obbB.center = b->GetBondbox()->GetCenter();
		obbB.axis[0] = b->GetRight();
		obbB.axis[1] = b->GetUp();
		obbB.axis[2] = b->GetForward();
		   
		obbB.length[0] = fabs(b->GetBondbox()->GetExtents().x * b->GetScale().x);
		obbB.length[1] = fabs(b->GetBondbox()->GetExtents().y * b->GetScale().y);
		obbB.length[2] = fabs(b->GetBondbox()->GetExtents().z * b->GetScale().z);

		double c[3][3];
		double absC[3][3];
		double d[3];
		double r0, r1, r;
		int i;
		const double cutoff = 0.999999;
		bool existsParallelPair = false;
		jbMath::Vector3 diff = a->GetBondbox()->GetCenter() - b->GetBondbox()->GetCenter();

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				c[i][j] = jbMath::Vector3::Dot(obbA.axis[i], obbB.axis[j]);
				absC[i][j] = fabs(c[i][j]);
				if (absC[i][j] > cutoff) existsParallelPair = true;
			}
			d[i] = jbMath::Vector3::Dot(obbA.axis[i], diff);
		}

		for (int i = 0; i < 3; i++)
		{
			r = fabs(d[i]);
			r0 = obbA.length[i];
			r1 = absC[i][0] * obbB.length[0] +
				absC[i][1] * obbB.length[1] +
				absC[i][2] * obbB.length[2];

			if (r > r0 + r1) return false;
		}
		for (int i = 0; i < 3; i++)
		{
			r = fabs(jbMath::Vector3::Dot(obbB.axis[i], diff));
			r0 = obbB.length[i];
			r1 = absC[i][0] * obbA.length[0] +
				absC[i][1] * obbA.length[1] +
				absC[i][2] * obbA.length[2];

			if (r > r0 + r1) return false;
		}
		if (existsParallelPair) return true;

		r = fabs(d[2] * c[1][0] - d[1] * c[2][0]);
		r0 = obbA.length[1] * absC[2][0] + obbA.length[2] * absC[1][0];
		r1 = obbB.length[1] * absC[0][2] + obbB.length[2] * absC[0][1];
		if (r > r0 + r1) return false;

		r = fabs(d[2] * c[1][1] - d[1] * c[2][1]);
		r0 = obbA.length[1] * absC[2][1] + obbA.length[2] * absC[1][1];
		r1 = obbB.length[1] * absC[0][2] + obbB.length[2] * absC[0][1];
		if (r > r0 + r1) return false;

		r = fabs(d[2] * c[1][2] - d[1] * c[2][2]);
		r0 = obbA.length[1] * absC[2][2] + obbA.length[2] * absC[1][2];
		r1 = obbB.length[1] * absC[0][1] + obbB.length[2] * absC[0][0];
		if (r > r0 + r1) return false;

		r = fabs(d[0] * c[2][0] - d[2] * c[0][0]);
		r0 = obbA.length[0] * absC[2][0] + obbA.length[2] * absC[0][0];
		r1 = obbB.length[1] * absC[1][2] + obbB.length[2] * absC[1][1];
		if (r > r0 + r1) return false;

		r = fabs(d[0] * c[2][1] - d[2] * c[0][1]);
		r0 = obbA.length[0] * absC[2][2] + obbA.length[2] * absC[0][1];
		r1 = obbB.length[0] * absC[1][2] + obbB.length[2] * absC[1][0];
		if (r > r0 + r1) return false;

		r = fabs(d[0] * c[2][2] - d[2] * c[0][2]);
		r0 = obbA.length[0] * absC[2][2] + obbA.length[2] * absC[0][2];
		r1 = obbB.length[0] * absC[1][1] + obbB.length[1] * absC[1][0];
		if (r > r0 + r1) return false;

		r = fabs(d[1] * c[0][0] - d[0] * c[1][0]);
		r0 = obbA.length[0] * absC[1][0] + obbA.length[1] * absC[0][0];
		r1 = obbB.length[1] * absC[2][2] + obbB.length[2] * absC[2][1];
		if (r > r0 + r1) return false;

		r = fabs(d[1] * c[0][1] - d[0] * c[1][1]);
		r0 = obbA.length[0] * absC[1][1] + obbA.length[1] * absC[0][1];
		r1 = obbB.length[0] * absC[2][2] + obbB.length[2] * absC[2][0];
		if (r > r0 + r1) return false;

		r = fabs(d[1] * c[0][2] - d[0] * c[1][2]);
		r0 = obbA.length[0] * absC[1][2] + obbA.length[1] * absC[0][2];
		r1 = obbB.length[0] * absC[2][1] + obbB.length[1] * absC[2][0];
		if (r > r0 + r1) return false;

		return true;
	}
	BOOL SphereCollision(cBoundbox * A, cBoundbox * B)
	{
		jbMath::Vector3 aMax = A->max;
		jbMath::Vector3 aMin = A->min;

		jbMath::Vector3 bMax = B->max;
		jbMath::Vector3 bMin = B->min;

		jbMath::Vector3 aCenter = (aMax + aMin) * 0.5f;
		jbMath::Vector3 bCenter = (bMax + bMin) * 0.5f;

		jbMath::Vector3 aRadius = (aMax - aCenter) * 0.5f;
		jbMath::Vector3 bRadius = (bMax - bCenter) * 0.5f;
		
		float d = (aCenter - bCenter).Length();
		float r = (aRadius + bRadius).Length();

		if (d <= r) return true;

		return false;

	}
	BOOL FrustumCulling(cFigure * pF, jbMath::Matrix viewproj)
	{
		std::vector<jbMath::Vector3> fs(frustum.size());
		
		pF->GetBondbox()->SetBB(pF->GetWorld());

		float w;
		jbMath::Matrix invers = viewproj.Inverse(w) * jbMath::Scale(jbMath::Vector3(0.8, 0.8, 0.8));
		
		for (int i = 0; i < fs.size(); i++)
		{
			fs[i] = frustum[i].TransformCoord(&invers);
		}

		plane p[6];

		GetPlane(&p[0], fs[0], fs[1], fs[2]); // near
		GetPlane(&p[1], fs[4], fs[5], fs[1]); // left
		GetPlane(&p[2], fs[3], fs[2], fs[6]); // right
		GetPlane(&p[3], fs[1], fs[5], fs[6]); // up
		GetPlane(&p[4], fs[4], fs[0], fs[3]); // down
		GetPlane(&p[5], fs[4], fs[6], fs[5]); // far

		jbMath::Vector3 center = pF->GetBondbox()->GetCenter();
		jbMath::Vector3 radius = pF->GetBondbox()->GetExtents();

		for (int i = 0; i < 6; i++)
		{
			float f = jbMath::Vector3::Dot(jbMath::Vector3(p[i].a, p[i].b, p[i].c), center) + p[i].d;

			if (f > radius.Length()) return false;
		//	if (f > EPSILON) return false;
		}

		return true;
	}
	void SetFrustum()
	{
		float r = 1.0f;
		frustum.push_back(jbMath::Vector3(-r, -r, 0)); // 0
		frustum.push_back(jbMath::Vector3(-r,  r, 0)); // 1
		frustum.push_back(jbMath::Vector3( r,  r, 0)); // 2
		frustum.push_back(jbMath::Vector3( r, -r, 0)); // 3
		frustum.push_back(jbMath::Vector3(-r, -r, r)); // 4
		frustum.push_back(jbMath::Vector3(-r,  r, r)); // 5
		frustum.push_back(jbMath::Vector3( r,  r, r)); // 6
		frustum.push_back(jbMath::Vector3( r, -r, r)); // 7

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
	void GetPlane(plane * pl, jbMath::Vector3 p0, jbMath::Vector3 p1, jbMath::Vector3 p2)
	{
		jbMath::Vector3 v1 = p1 - p0;
		jbMath::Vector3 v2 = p2 - p0;
		jbMath::Vector3 normal = jbMath::Vector3::cross(v1, v2).Normalize();
		
		pl->d = -jbMath::Vector3::Dot(normal, p0);
		//normal = normal.Normalize();
		pl->a = normal.x;
		pl->b = normal.y;
		pl->c = normal.z;
	}
	void draw(CDC * pDC, cCamera pCamera, jbMath::Matrix vp)
	{
		CArray<CPoint, CPoint> arrP;
		float w;
		jbMath::Matrix invers = pCamera.GetViewProj().Inverse(w);
		for (int i = 0; i < indices.size(); i += 3)
		{
			jbMath::Vector3 v1 = frustum[indices[i + 0]];
			jbMath::Vector3 v2 = frustum[indices[i + 1]];
			jbMath::Vector3 v3 = frustum[indices[i + 2]];

			v1 = v1.TransformCoord(&invers);
			v2 = v2.TransformCoord(&invers);
			v3 = v3.TransformCoord(&invers);

			CPen pen;
			pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			CPen* oldPen = pDC->SelectObject(&pen);

			v1 = v1.TransformCoord(&vp);
			v2 = v2.TransformCoord(&vp);
			v3 = v3.TransformCoord(&vp);

			arrP.Add(CPoint(v1.x, v1.y));
			arrP.Add(CPoint(v2.x, v2.y));
			arrP.Add(CPoint(v3.x, v3.y));

			pDC->Polygon(&arrP[0], arrP.GetCount());
			arrP.RemoveAll();
			pDC->SelectObject(oldPen);
		}
	}
}
