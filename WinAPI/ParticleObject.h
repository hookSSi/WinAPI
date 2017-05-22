#pragma once
#include "stdafx.h"
#include "Object.h"

class ParticleObject : public Object
{
public:
	float lifeTime; // 생명시간
	chrono::system_clock::time_point previousTime = { currentTime }; // 이전 시간값

	ParticleObject():Object(),lifeTime(0){};
	~ParticleObject(){};

	virtual void Init(){};
	virtual void Draw(HWND hWnd, HDC hdc){}; // 랜더링
	virtual bool Update(){ return true; } // 게임 오브젝트 업데이트
};