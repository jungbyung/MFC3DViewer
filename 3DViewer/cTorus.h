#pragma once
#include "cFigure.h"

class cTorus : public cFigure
{
public:
	cTorus();
	~cTorus();

	virtual HRESULT Init() override;
	virtual void update() override;
	virtual void release() override;
//	virtual void draw(CDC* pDC, cCamera pCamera, jbMath::Matrix vp, cLight* light) override;
//	virtual void SelectDraw(CDC* pDC, cCamera pCamera, jbMath::Matrix vp, cLight* light) override;
};

