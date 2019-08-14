#pragma once


class cCamera
{
private:
	jbMath::Vector3 forward;
	jbMath::Vector3 up;
	jbMath::Vector3 lookat;
	
	jbMath::Matrix view;
	jbMath::Matrix proj;

	jbMath::Matrix world;

	bool m_isBtDown;
	CPoint m_ptMouse;

	float angleX;
	float angleY;
	float dist;
public:
	cCamera();
	~cCamera();

	HRESULT init();
	void update();
	void release();
	void draw();
	jbMath::Vector3 pos;

	jbMath::Matrix GetView() { return view; }
	jbMath::Matrix GetProj() { return proj; }
	jbMath::Matrix GetViewProj() { return view * proj; }
	//jbMath::Matrix GetViewProj(jbMath::Vector3 vec)
	//{
	//
	//
	//	pos = jbMath::Vector3(0, 0, dist);
	//
	//	jbMath::Matrix matrx, matry;
	//	matrx = jbMath::RotateX(angleX);
	//	matry = jbMath::RotateY(angleY);
	//
	//	pos = pos.TransformCoord(&(matrx * matry));
	//
	//	jbMath::Vector3 p = pos + vec;
	//
	//	jbMath::Matrix v;
	//	v = jbMath::View(&p, &up, &vec);
	//
	//	return v * proj; 
	//}

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	jbUtill::Ray GetRay(CPoint pt, CRect rt);

	void SetParallel();
	void SetPerspective();

	jbMath::Vector3 GetForward() { return forward.Normalize(); }
	jbMath::Matrix GetWorld() { return world; }
};

