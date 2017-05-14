#pragma once
#include "stdafx.h"
#include "Component.h"

class Collision :public Component
{
public:
	bool debug; // 디버그용 출력 활성화?
	Vector2D position; // 위치
	Vector2D scale; // 크기

	Collision() : debug(false){}
	virtual ~Collision(){}
	virtual bool Update();
	virtual bool Draw(HWND hWnd, HDC hdc);
};