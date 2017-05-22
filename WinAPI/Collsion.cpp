#include "Collision.h"

// 충돌 처리 업데이트
bool Collision::Update(Vector2D& pos)
{
	if (isActive)
	{
		this->position = pos;
		return true; // 컴포넌트가 Active 되어 있어 Update가 실행됨
	}
	return false; // 컴포넌트가 Active 되어 있지 않음
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
	// 두원 사이의 거리 > 둘 중 큰 반지름 = 충돌 없음
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