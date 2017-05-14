#pragma once
#include "stdafx.h"
#include "Component.h"

class Collision :public Component
{
public:
	bool debug; // ����׿� ��� Ȱ��ȭ?
	Vector2D position; // ��ġ
	Vector2D scale; // ũ��

	Collision() : debug(false){}
	virtual ~Collision(){}
	virtual bool Update();
	virtual bool Draw(HWND hWnd, HDC hdc);
};