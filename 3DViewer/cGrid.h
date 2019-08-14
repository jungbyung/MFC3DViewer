#pragma once
class cCamera;

class cGrid
{
private:
	std::vector<jbMath::Vector3> line;
	int n;
	float f;
public:
	cGrid();
	~cGrid();


	void Setup();
	void draw(CDC* pDC, cCamera pCamera, jbMath::Matrix vp);

};

