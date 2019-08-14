#pragma once
#include <vector>
class cLight;
class cCamera;
class cBoundbox;
class cPyramid;

class cFigure
{
protected:
	std::vector<jbUtill::vertex> vertices;
	std::vector<int> indices;

	jbMath::Vector3 pos;
	jbMath::Vector3 angle;
	jbMath::Vector3 scale;

	jbMath::Matrix world;

	bool isWire;

	cBoundbox* m_pBoundbox;
	cPyramid* m_pPyramid;

	jbMath::Vector3 color;
	jbMath::Vector3 wireColor;

	jbMath::Vector3 forward;
	jbMath::Vector3 up;
	jbMath::Vector3 right;
public:
	cFigure();
	virtual ~cFigure();

	virtual HRESULT Init() = 0;
	virtual void update();
	virtual void release() = 0;
	virtual void draw(CDC* pDC, cCamera pCamera, jbMath::Matrix vp, cLight* light);
	virtual void SelectDraw(CDC* pDC, cCamera pCamera, jbMath::Matrix vp, cLight* light);

	void Moving();

	std::vector<jbUtill::vertex> GetVertices() const { return vertices; }
	std::vector<int> GetIndices() const { return indices; }

	jbMath::Matrix GetWorld() const { return world; }

	void SetPosition(jbMath::Vector3 vec);
	void SetRotate(jbMath::Vector3 vec);
	void SetScale(jbMath::Vector3 vec);

	void SetWire(bool s) { isWire = s; }

	jbMath::Vector3 GetPosition() { return pos; }
	jbMath::Vector3 GetScale() { return scale; }
	jbMath::Vector3 GetRotate() { return angle; }

	cBoundbox* GetBondbox() { return m_pBoundbox; }

	cPyramid* GetPyramid() { return m_pPyramid; }

	void SetColor(jbMath::Vector3 vec) { color = vec; }
	void SetWireColor(jbMath::Vector3 vec) { wireColor = vec; }

	jbMath::Vector3 GetForward() { return forward; }
	jbMath::Vector3 GetUp() { return up; }
	jbMath::Vector3 GetRight() { return right; }

	
};

