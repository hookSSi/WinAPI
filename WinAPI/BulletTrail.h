#pragma once
#include "stdafx.h"
#include "ParticleObject.h"

class BulletTrailObject : public ParticleObject
{
public:
	BulletTrailObject(){};
	~BulletTrailObject(){};

	virtual void Init();
	virtual void Draw(HWND hWnd, HDC hdc); // ������
	virtual bool Update(); // ������Ʈ
};