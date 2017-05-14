#include "Tank.h"

Tank::Tank() : Object(), velocity(0), fireDelay(0), jumpDelay(0), dashDelay(0){ direction = Vector2D(1, 0); };

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

void Tank::Move(Vector2D p_direction)
{
	this->SetDirection(p_direction);
	this->position += (this->direction * this->velocity);
}

void Tank::Move(){	Move(this->direction);}

void Tank::Fire()
{

}

void Tank::Jump()
{

}

void Tank::Dash()
{

}