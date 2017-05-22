#pragma once
#include "stdafx.h"
#include "Singleton.h"

//���� ����
class ParticleObject;

class ParticleManager : public Singleton<ParticleManager>
{
public:
	ParticleManager(){};
	~ParticleManager(){};

	void Update();
	void Draw(HWND hWnd, HDC hdc);
	void AddObject(ParticleObject* object);
private:
	list<ParticleObject*> objectList;
};