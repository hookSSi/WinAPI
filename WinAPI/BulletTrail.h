#pragma once
#include "stdafx.h"
#include "ParticleObject.h"

class BulletTrailObject : public ParticleObject
{
public:
	BulletTrailObject(){};
	~BulletTrailObject(){};

	virtual void Init();
	virtual void Draw(HWND hWnd, HDC hdc); // 랜더링
	virtual bool Update(); // 업데이트
};