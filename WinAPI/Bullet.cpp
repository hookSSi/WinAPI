#include "Bullet.h"
#include "Game.h"
#include "Map.h"
#include "Physics.h"

int Bullet::counter = 1;

Bullet::Bullet() :Object()
{
	counter++;
}

bool Bullet::FixedUpdate(float time)
{
	this->position += this->velocity * time;

	return true;
}

bool Bullet::Update()
{ 
	Map map = Game::GetInstance()->GetMap();

	/*bool IsCollision = Raycast(map, lastPosition.x, lastPosition.y, position.x, position.y);

	if (IsCollision)
	{
		Explode(5);
	}*/

	if (!position.isValid())
		this->SelfDestroy();

	return true;
}

bool Bullet::Explode(int radius)
{
	Map map = Game::GetInstance()->GetMap();

	for (int x = position.x - radius; x <= position.x + radius; x++)
	{
		for (int y = position.y - radius; y <= position.y + radius; x++)
		{
			if (IsValidPos(x, y)) // À¯È¿ÇÑ ÁÂÇ¥?
			{
				if (pow(x - position.x, 2) + pow(y - position.y, 2) <= radius * radius)
				{
					if (map.IsPixelSolid(x, y))
					{
						map.RemoveStaticPixel(x, y);
					}
				}
			}
		}
	}

	this->SelfDestroy();

	return true;
}

void Bullet::Draw(HWND hWnd, HDC hdc)
{
	HBRUSH MyBrush, OldBrush;
	HPEN MyPen, OldPen;

	MyPen = CreatePen(PS_SOLID, 1, WHITE_COLOR);
	OldPen = (HPEN)SelectObject(hdc, MyPen);

	MyBrush = (HBRUSH)CreateSolidBrush(WHITE_COLOR);
	OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);


	float left = this->position.x - GetSize().x;
	float top = this->position.y - GetSize().y;
	float right = this->position.x + GetSize().x;
	float bottom = this->position.y + GetSize().y;

	Rectangle(hdc, left, top, right, bottom);

	SelectObject(hdc, OldPen);
	DeleteObject(MyPen);
	SelectObject(hdc, OldBrush);
	DeleteObject(MyBrush);
}