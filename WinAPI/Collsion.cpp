#include "Collision.h"

// �浹 ó�� ������Ʈ
bool Collision::Update(Vector2D& pos, Vector2D& lastPos)
{
	if (isActive)
	{
		this->position = pos;
		this->lastPosition = lastPos;
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

bool Collision::CollisionCheck(Collision* other)
{
	
	int delta_x = abs(other->lastPosition.x - other->position.x);
	int delta_y = abs(other->lastPosition.y - other->position.y);

	int x = other->lastPosition.x;
	int y = other->lastPosition.y;

	int xinc1, xinc2, yinc1, yinc2;

	if (other->lastPosition.x <= other->position.x)
	{
		xinc1 = 1;
		xinc2 = 1;
	}
	else
	{
		xinc1 = -1;
		xinc2 = -1;
	}
	if (other->lastPosition.y <= other->position.y)
	{
		yinc1 = 1;
		yinc2 = 1;
	}
	else
	{
		yinc1 = -1;
		yinc2 = -1;
	}

	int den, num, numadd, numpixels;
	if (delta_x >= delta_y)
	{
		xinc1 = 0;
		yinc2 = 0;
		den = delta_x;
		num = delta_x / 2;
		numadd = delta_y;
		numpixels = delta_x;
	}
	else
	{
		xinc2 = 0;
		yinc1 = 0;
		den = delta_y;
		num = delta_y / 2;
		numadd = delta_x;
		numpixels = delta_y;
	}

	int prevX = other->lastPosition.x;
	int prevY = other->lastPosition.y;

	for (int curpixel = 0; curpixel <= numpixels; curpixel++)
	{
		// �ο� ������ �Ÿ� > ��A ������ + ��B ������ = �浹 ����
		if (VectorMath::GetDistance(Vector2D(x, y), this->position) > this->radius + other->radius)
		{
			this->isCollision = false;
		}
		else
		{
			this->isCollision = true;
			return this->isCollision;
		}

		prevX = x;
		prevY = y;

		num += numadd;

		if (num >= den)
		{
			num -= den;
			x += xinc1;
			y += yinc1;
		}

		x += xinc2;
		y += yinc2;
	}

	return this->isCollision;
}