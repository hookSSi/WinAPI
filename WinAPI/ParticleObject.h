#pragma once
#include "stdafx.h"
#include "Object.h"

class ParticleObject : public Object
{
public:
	float lifeTime; // ����ð�
	chrono::system_clock::time_point previousTime = { currentTime }; // ���� �ð���

	ParticleObject():Object(),lifeTime(0){};
	~ParticleObject(){};

	virtual void Init(){};
	virtual void Draw(HWND hWnd, HDC hdc){}; // ������
	virtual bool Update(){ return true; } // ���� ������Ʈ ������Ʈ
};