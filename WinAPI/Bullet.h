#pragma once
#include "Object.h"

class Bullet : public Object
{
public:
	static int counter;
	Vector2D lastPosition;
	Vector2D velocity;

	Bullet();
	Bullet(Vector2D& p_postion){ this->position = p_postion; this->lastPosition = lastPosition; }
	~Bullet(){ counter--; };

	virtual void Draw(HWND hWnd, HDC hdc);
	bool FixedUpdate(float time);
	bool Update();

	bool SetPosition(Vector2D& pos){ this->position = pos; this->lastPosition = pos; return true; }

	bool SelfDestroy(){ this->isActive = false; return true; }
private:
	bool Explode(int radius);
};