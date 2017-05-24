#pragma once
#include "stdafx.h"
#include "Component.h"

class Collision :public Component
{
public:
	Vector2D lastPosition;
	Vector2D position;
	float radius; // 반지름
	bool isCollision; // 충돌됨?

	bool debug; // 디버그용 출력 활성화?

	Collision() : debug(true),radius(10),isCollision(false){}
	virtual ~Collision(){}
	virtual bool Update(Vector2D& pos,Vector2D& lastPos);
	virtual bool Draw(HWND hWnd, HDC hdc);
	bool CollisionCheck(Collision* other);
};