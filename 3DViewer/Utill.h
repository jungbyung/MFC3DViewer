#pragma once
class cFigure;
class cBoundbox;
class cPyramid;
class cMesh;
class cCamera;
namespace jbUtill
{
	static std::vector<jbMath::Vector3> frustum;
	static std::vector<int> indices;
	struct vertex
	{
		jbMath::Vector3 pos;
		jbMath::Vector3 color;

		vertex() {}
		vertex(jbMath::Vector3 p, jbMath::Vector3 c) : pos(p), color(c) {}
	};

	struct pcn
	{
		jbMath::Vector3 pos;
		jbMath::Vector3 color;
		jbMath::Vector3 normal;
		pcn() {}
		pcn(jbMath::Vector3 p, jbMath::Vector3 c, jbMath::Vector3 n) : pos(p), color(c), normal(n) {}
	};

	jbMath::Vector3 ComputeNormal(jbMath::Vector3 p0, jbMath::Vector3 p1, jbMath::Vector3 p2);

	DWORD GetRGB(jbMath::Vector3 vec);

	struct Ray
	{
		jbMath::Vector3 ori;
		jbMath::Vector3 dir;
	};

	struct plane
	{
		float a, b, c, d;
	};

	BOOL ComputeRayCast(Ray ray, cFigure* fig);
	BOOL ComputeRayCast(Ray ray, cMesh* pMesh);
	BOOL ComputeRayCast(Ray ray, cPyramid* fig, int& n, jbMath::Matrix parent = jbMath::Matrix::Identity());

	BOOL AABBCollision(cBoundbox* A, cBoundbox* B);
	BOOL OBBCollision(cFigure* a, cFigure* b);
	BOOL SphereCollision(cBoundbox* A, cBoundbox* B);

	BOOL FrustumCulling(cFigure* pF, jbMath::Matrix viewproj = jbMath::Matrix::Identity());
	void SetFrustum();

	void GetPlane(plane* pl, jbMath::Vector3 p0, jbMath::Vector3 p1, jbMath::Vector3 p2);
	void draw(CDC* pDC, cCamera pCamera, jbMath::Matrix vp);
}