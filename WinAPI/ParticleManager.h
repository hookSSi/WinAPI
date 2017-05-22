#pragma once
#include "stdafx.h"
#include "Singleton.h"

//전방 선언
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