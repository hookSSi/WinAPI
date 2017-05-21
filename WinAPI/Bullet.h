#pragma once
#include "Object.h"

class Bullet : public Object
{
public:
	Vector2D lastPosition;
	Vector2D velocity;

	Bullet();
	Bullet(Vector2D& p_postion){ type = OBJECT_TYPE::BULLET; this->position = p_postion; this->lastPosition = lastPosition; }
	~Bullet(){};

	virtual void Draw(HWND hWnd, HDC hdc);
	bool FixedUpdate(float time);
	bool Update();

	bool SetPosition(Vector2D& pos){ this->position = pos; this->lastPosition = pos; return true; }
private:
	bool Explode(int radius);
};