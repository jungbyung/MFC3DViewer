#pragma once

class cCamera;
class cCube;
class cLight;
class cSphere;
class cTorus;
class cFigure;
class cMesh;
class cGrid;
class cPyramid;
class cnewCube;

class cMain
{
private:
	cCamera* m_pCamera;

	cLight* m_pDirectionLight;

	jbMath::Matrix vp;

	cMesh* m_pMesh;
	CPoint m_ptMouse;
	bool m_isClick;
	bool isMoving;
	int axis;
	cFigure* m_pCurrentFigure;
	cMesh* m_pCurrentMesh;
	std::vector<cMesh*> m_vMesh;
	std::vector<cFigure*> m_vFigures;

	std::map<float, int> z_order;
	std::vector<float> zz;

	int m_nFigureNum;

	cGrid* m_pGrid;

	int prevpx;

public:
	cMain();
	~cMain();

	char* pStr;
	CString str;

	HRESULT Init();
	void Update();
	void Release();
	void Draw(CDC* pDC);

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


	void SetParallel();
	void SetPerspective();

	void AddFigure(int n);

	void SetWire();
	void SetSolid();

	void SetColor(jbMath::Vector3 vec);
	void SetWireColor(jbMath::Vector3 vec);

};

