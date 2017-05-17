#include "Tank.h"

Tank::Tank() : Object(), fireDelay(0), jumpDelay(0), dashDelay(0){ velocity = Vector2D(1, 0); };

void Tank::Draw(HWND hWnd, HDC hdc)
{
	HBRUSH MyBrush, OldBrush;

	MyBrush = (HBRUSH)CreateSolidBrush(RGB(255,255,255));
	OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);

	float left = this->position.x - GetSize().x;
	float top = this->position.y - GetSize().y;
	float right = this->position.x + GetSize().x;
	float bottom = this->position.y + GetSize().y;

	Rectangle(hdc, left, top, right, bottom);
}

bool Tank::Update()
{
	if (isActive)
	{
		return true;
	}
	return false;
}

void Tank::Move(Vector2D& p_velocity)
{
	this->position += this->velocity;
}

void Tank::Move(){	Move(this->velocity);}

void Tank::Fire()
{

}

void Tank::Jump()
{

}

void Tank::Dash()
{

}