#pragma once
#include "stdafx.h"
#include "Component.h"

class Collision :public Component
{
public:
	Vector2D position;
	float radius; // ������
	bool isCollision; // �浹��?

	bool debug; // ����׿� ��� Ȱ��ȭ?

	Collision() : debug(true),radius(10),isCollision(false){}
	virtual ~Collision(){}
	virtual bool Update(Vector2D& pos);
	virtual bool Draw(HWND hWnd, HDC hdc);
	bool CollisionCheck(Collision& other);
};