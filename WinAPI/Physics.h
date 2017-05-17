#pragma once
#include "Singleton.h"
#include "stdafx.h"

// ���漱��
class Object;

class Physics: public Singleton<Physics>{
public:
	chrono::system_clock::time_point previousTime = chrono::system_clock::now(); // ���� �ð�
	chrono::system_clock::time_point currentTime = chrono::system_clock::now(); // ���� �ð�
	int leftOverDeltaTie; // ���� �ð�
	const float fixedDeltaTime;

	bool Update();

	void AddObject(Object* object){ object_list.push_back(object); }

	Physics() :leftOverDeltaTie(0), fixedDeltaTime(FPS / 1000.0f){}
	virtual ~Physics(){}
private:
	vector<Object*> object_list;
};