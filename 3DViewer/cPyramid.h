#pragma once

class cCamera;

class cPyramid
{
private:
	std::vector<jbMath::Vector3> vertices;
	std::vector<int> indices;
public:
	cPyramid();
	~cPyramid();

	void init(jbMath::Vector3 center);
	void draw(CDC* pDC, cCamera pCamera, jbMath::Matrix vp, jbMath::Matrix mat = jbMath::Matrix::Identity());
	
	std::vector<jbMath::Vector3> GetVertices() { return vertices; }
	std::vector<int> GetIndices() { return indices; }
};

