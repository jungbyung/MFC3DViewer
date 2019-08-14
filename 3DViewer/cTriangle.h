#pragma once
#include "cFigure.h"

class cTriangle : public cFigure
{
public:
	cTriangle();
	~cTriangle();

	virtual HRESULT Init() override;
	virtual void update() override;
	virtual void release() override;
};

