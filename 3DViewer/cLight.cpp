#include "stdafx.h"
#include "cLight.h"


cLight::cLight()
	: dir(jbMath::Vector3(0, 0, 1))
	, rgb(jbMath::Vector3(255, 255, 255))
	, dwRGB(RGB(255,255,255))
	, y(0.f)
	, ambient(jbMath::Vector3(0.1f, 0.1f, 0.1f))
{
}


cLight::~cLight()
{
}

HRESULT cLight::init()
{
	dir = dir.Normalize();
	return S_OK;
}

void cLight::release()
{
}

void cLight::update()
{
	//dir = jbMath::Vector3(0, 0, 1);
	if (GetKeyState(VK_NUMPAD7) & 0x8000)
	{
		y += 0.01f;
	}
	if (GetKeyState(VK_NUMPAD8) & 0x8000)
	{
		y -= 0.01f;
	}

	jbMath::Matrix rot = jbMath::RotateY(y);

	//dir = jbMath::Vector3(0, 0, 1).TransformNormal(&rot);
	dir = dir.TransformNormal(&rot);
	dir = dir.Normalize();
}

void cLight::draw()
{
}
