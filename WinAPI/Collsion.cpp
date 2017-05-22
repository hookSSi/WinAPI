#include "Collision.h"

// �浹 ó�� ������Ʈ
bool Collision::Update(Vector2D& pos)
{
	if (isActive)
	{
		this->position = pos;
		return true; // ������Ʈ�� Active �Ǿ� �־� Update�� �����
	}
	return false; // ������Ʈ�� Active �Ǿ� ���� ����
}

bool Collision::Draw(HWND hWnd, HDC hdc)
{
	HPEN MyPen, OldPen;

	MyPen = CreatePen(PS_DOT, 1, GREEN_COLOR);
	OldPen = (HPEN)SelectObject(hdc, MyPen);

	HBRUSH MyBrush, OldBrush;

	MyBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);

	float left = this->position.x - radius;
	float top = this->position.y - radius;
	float right = this->position.x + radius;
	float bottom = this->position.y + radius;

	Ellipse(hdc, left, top, right, bottom);

	SelectObject(hdc, OldPen);
	DeleteObject(MyPen);

	return true;
}

bool Collision::CollisionCheck(Collision& other)
{
	// �ο� ������ �Ÿ� > �� �� ū ������ = �浹 ����
	int maxRadius = this->radius >= other.radius ? this->radius : other.radius;

	if (VectorMath::GetDistance(this->position, other.position) > maxRadius)
	{
		this->isCollision = false;
	}
	else
	{
		this->isCollision = true;
	}

	return this->isCollision;
}