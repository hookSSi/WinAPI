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

	Vector2D gravityAmt;
	bool isGravity; // �߷�?

	bool Update();

	void AddObject(Object* object){ object_list.push_back(object); }
	void DeleteObject(Object* object);

	Physics() :leftOverDeltaTie(0), fixedDeltaTime(FPS / 1000.0f), isGravity(true){ gravityAmt = Vector2D(0.0f, 9.8f); }
	virtual ~Physics(){}
private:
	list<Object*> object_list;
};