#pragma once
#include "Object.h"

class Bullet : public Object
{
public:
	Vector2D lastPosition;
	Vector2D velocity;

	Bullet() :Object(){};
	Bullet(Vector2D p_postion){ this->position = p_postion; this->lastPosition = lastPosition; }
	~Bullet(){};

	virtual void Draw(HWND hWnd, HDC hdc);
	bool FixedUpdate(float time);
	bool Update();
private:
	bool Explode(int radius);
};