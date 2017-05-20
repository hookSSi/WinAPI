#include "Bullet.h"
#include "Game.h"
#include "Map.h"
#include "Physics.h"
#include "Scene.h"

int Bullet::counter = 1;

Bullet::Bullet() :Object()
{
	counter++;
}

bool Bullet::FixedUpdate(float time)
{
	this->lastPosition = this->position;
	this->position += this->velocity * time;

	return true;
}

bool Bullet::Update()
{ 
	bool IsCollision = Raycast(lastPosition.x, lastPosition.y, position.x, position.y);

	if (IsCollision)
	{
		Explode(10);
	}
	else
	{
		if (!position.isValid())
			this->SelfDestroy();
	}

	return true;
}

bool Bullet::Explode(int radius)
{
	Map *map = Game::GetInstance()->GetMap();
	
	for (int x = position.x - radius; x <= position.x + radius; x++)
	{
		for (int y = position.y - radius; y <= position.y + radius; y++)
		{
			if (IsValidPos(x, y)) // ��ȿ�� ��ǥ?
			{
				float length = ((x - position.x) * (x - position.x) + (y - position.y) * (y - position.y));
				float r = radius * radius;

				if (length <= r)
				{
					if (map->IsPixelSolid(x, y))
					{
						map->RemoveStaticPixel(x, y);

						/* ���� �ȼ� ���� */
						Dynamic_Pixel *pixel = new Dynamic_Pixel();

						pixel->SetPosition(Vector2D(x, y));
						pixel->SetSize(Vector2D(3, 3));

						float distanceRate = 1 - length / r;
						float speed = 200 * distanceRate;

						float xDiff = x - position.x;
						float yDiff = y - position.y;

						float velX = speed * (xDiff + (rand() % 20 - 10));
						float velY = speed * (yDiff + (rand() % 20 - 10));

						pixel->velocity = Vector2D(velX, velY);

						string str = "pixel";

						Scene *scene = Game::GetInstance()->GetScene();

						bool success = scene->AddGameObject(str, pixel);

						if (success)
						{
							Physics::GetInstance()->AddObject(pixel);
						}
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