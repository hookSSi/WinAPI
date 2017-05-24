#pragma once
#include "Singleton.h"
#include "stdafx.h"

// ���漱��
class Object;

class Physics: public Singleton<Physics>{
public:
	chrono::system_clock::time_point previousTime = chrono::system_clock::now(); // ���� �ð�
	int leftOverDeltaTie; // ���� �ð�
	const float fixedDeltaTime;

	Vector2D gravityAmt;
	bool isGravity; // �߷�?

	bool Update(); // ���� ������Ʈ
	void CollisionCheck(); // �浹 üũ

	Tank* player1_tank = nullptr; // �÷��̾� 1 ��ũ
	Tank* player2_tank = nullptr; // �÷��̾� 2 ��ũ

	void AddObject(Object* object);
	void DeleteObject(Object* object);
	void DeleteAllObject();

	Physics() :leftOverDeltaTie(0), fixedDeltaTime(FPS / 1000.0f), isGravity(true){ gravityAmt = Vector2D(0.0f, 9.8f); }
	virtual ~Physics(){}
private:
	list<Object*> object_list;
};