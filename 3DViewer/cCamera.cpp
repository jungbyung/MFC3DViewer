#include "stdafx.h"
#include "cCamera.h"


cCamera::cCamera()
	: dist(5.0f)
	, angleX(0.f)
	, angleY(0.f)
{
}


cCamera::~cCamera()
{
}

HRESULT cCamera::init()
{
	CRect rc;
	GetClientRect(g_hWnd, &rc);
	view = jbMath::Matrix::Identity();

	lookat = jbMath::Vector3(0, 0, 0);
	pos = jbMath::Vector3(0, 0, dist);
	up = jbMath::Vector3(0, 1, 0);
	view = jbMath::View(&pos, &up, &lookat);

	proj = jbMath::Matrix::Identity();

	proj = jbMath::Proj(PI * 0.25f, static_cast<float>(rc.right / (float)rc.bottom), 1, 1000);

	m_isBtDown = false;
	//proj = jbMath::Proj();
	world = jbMath::Matrix::Identity();
	return S_OK;
}

void cCamera::update()
{
	pos = jbMath::Vector3(0, 0, -dist);

	jbMath::Matrix matrx, matry;
	matrx = jbMath::RotateX(angleX);
	matry = jbMath::RotateY(angleY);

	pos = pos.TransformCoord(&(matrx * matry));

	forward = (lookat - pos).Normalize();
	world = matrx * matry;
	view = jbMath::View(&pos, &up, &lookat);
}

void cCamera::release()
{
}

void cCamera::draw()
{
}

void cCamera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_RBUTTONDOWN:
		m_isBtDown = true;
		m_ptMouse.x = LOWORD(lParam);
		m_ptMouse.y = HIWORD(lParam);
		break;
	case WM_RBUTTONUP:
		m_isBtDown = false;
		break;
	case WM_MOUSEMOVE:
		if (m_isBtDown)
		{
			CPoint ptCurr;
			ptCurr.x = LOWORD(lParam);
			ptCurr.y = HIWORD(lParam);

			CPoint ptDelta;
			ptDelta.x = ptCurr.x - m_ptMouse.x;
			ptDelta.y = ptCurr.y - m_ptMouse.y;

			angleX += (ptDelta.y / 1000.0f);
			angleY += (ptDelta.x / 1000.0f);

			if (angleX > PI / 2.f - EPSILON)
				angleX = PI / 2.f - EPSILON;
			if (angleX < -PI / 2.f + EPSILON)
				angleX = PI / 2.f + EPSILON;
			m_ptMouse = ptCurr;
		}
		break;
	case WM_MOUSEWHEEL:
		dist -= GET_WHEEL_DELTA_WPARAM(wParam) / 100.f;
		if (dist < 5.0f)
			dist = 5.0f;
		break;
	}
}

jbUtill::Ray cCamera::GetRay(CPoint pt, CRect rt)
{
	jbUtill::Ray ray;
	float x = (2.f * pt.x) / rt.Width() - 1.f;
	float y = 1.f - (2.f * pt.y) / rt.Height();
	
	ray.dir = jbMath::Vector3(x, y, 1.f);
	ray.ori = jbMath::Vector3(0, 0, 0);
	float f;
	jbMath::Matrix projinverse = proj.Inverse(f);
	jbMath::Matrix viewinverse = view.Inverse(f);

	ray.ori = ray.ori.TransformCoord(&projinverse);
	ray.dir = ray.dir.TransformCoord(&projinverse);
	ray.ori = ray.ori.TransformCoord(&viewinverse);
	ray.dir = ray.dir.TransformNormal(&viewinverse);

	ray.dir = ray.dir.Normalize();
	return ray;
}

void cCamera::SetParallel()
{
	CRect rc;
	GetClientRect(g_hWnd, &rc);
	proj = jbMath::Matrix::Identity();

	proj.m[0][0] = 0.1f;
	proj.m[1][1] = 0.1f;
	proj.m[2][2] = 0.1f;
}

void cCamera::SetPerspective()
{
	CRect rc;
	GetClientRect(g_hWnd, &rc);
	proj = jbMath::Proj(PI * 0.25f, static_cast<float>(rc.right / (float)rc.bottom), 1, 1000);
}
