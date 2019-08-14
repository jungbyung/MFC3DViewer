#pragma once

class cCamera;
class cLight;
class cBoundbox;

class cMesh
{
private:
	std::vector<jbUtill::pcn> vertices;
	std::vector<int> indices;
	
	jbMath::Vector3 pos;
	jbMath::Vector3 angle;
	jbMath::Vector3 scale;

	jbMath::Matrix world;

	bool isWire;
	cBoundbox* m_pBoundbox;

public:
	cMesh();
	~cMesh();

	void pushVertex(jbUtill::pcn v) { vertices.push_back(v); }
	void pushIndex(int n) { indices.push_back(n); }

	void init();
	void update();
	void release();
	void draw(CDC* pDC, cCamera pCamera, jbMath::Matrix vp, cLight* light);
	void SelectDraw(CDC* pDC, cCamera pCamera, jbMath::Matrix vp, cLight* light);
	void Moving();

	void SetPosition(jbMath::Vector3 vec);
	void SetRotate(jbMath::Vector3 vec);
	void SetScale(jbMath::Vector3 vec);

	void SetWire(bool s) { isWire = s; }

	std::vector<jbUtill::pcn> GetVertices() const { return vertices; }
	std::vector<int> GetIndices() const { return indices; }
	jbMath::Matrix GetWorld() const { return world; }
	cBoundbox* GetBondbox() const { return m_pBoundbox; }
};

