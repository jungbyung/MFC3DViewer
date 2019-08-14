#pragma once
class cCamera;

class cBoundbox
{
private:
	std::vector<jbMath::Vector3> vertices;
	std::vector<int> indices;

	jbMath::Vector3 vMax;
	jbMath::Vector3 vMin;
public:
	cBoundbox();
	~cBoundbox();

	void SetAABB(std::vector<jbUtill::vertex> v);
	void SetAABB(std::vector<jbUtill::pcn> v);
	void SetOBB(std::vector<jbUtill::vertex> v);

	void SetBB(jbMath::Matrix mat = jbMath::Matrix::Identity());

	void update(jbMath::Matrix mat = jbMath::Matrix::Identity());
	void draw(CDC* pDC, cCamera pCamera, jbMath::Matrix vp);
	

	jbMath::Vector3 min;
	jbMath::Vector3 max;

	jbMath::Vector3 GetExtents() { return (vMax - vMin) * 0.5f; }
	jbMath::Vector3 GetCenter() { return (max + min) * 0.5f; }

	std::vector<jbMath::Vector3> GetVertices() const { return vertices; }
	std::vector<int> GetIndices() const { return indices; }
};

