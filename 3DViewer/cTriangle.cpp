#include "stdafx.h"
#include "cTriangle.h"


cTriangle::cTriangle()
{
}


cTriangle::~cTriangle()
{
}

HRESULT cTriangle::Init()
{
	float r = 1.f;
	vertices.push_back(jbUtill::vertex(jbMath::Vector3(-r, -r, 0), jbMath::Vector3(1, 0.4f, 0)));
	vertices.push_back(jbUtill::vertex(jbMath::Vector3(r * cosf(PI/2), r, 0), jbMath::Vector3(1, 0.4f, 0)));
	vertices.push_back(jbUtill::vertex(jbMath::Vector3(r, -r, 0), jbMath::Vector3(1, 0.4f, 0)));

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	m_pBoundbox = nullptr;
	m_pPyramid = nullptr;

	return E_NOTIMPL;
}

void cTriangle::update()
{
	cFigure::update();
}

void cTriangle::release()
{
}
