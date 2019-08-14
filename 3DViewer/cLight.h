#pragma once


class cLight
{
public:
	jbMath::Vector3 dir;
	jbMath::Vector3 rgb;

	jbMath::Vector3 ambient;

	DWORD dwRGB;

	float y;
public:
	cLight();
	cLight(jbMath::Vector3 d) : dir(d) {}
	~cLight();

	HRESULT init();
	void release();
	void update();
	void draw();

	jbMath::Vector3 GetDir() const { return dir; }
};

