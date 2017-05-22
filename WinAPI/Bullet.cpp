#include "Bullet.h"
#include "Game.h"
#include "Map.h"
#include "Physics.h"
#include "Scene.h"
#include "ObjectPool.h"
#include "ParticleManager.h"
#include "BulletTrail.h"

Bullet::Bullet() :Object()
{
	type = OBJECT_TYPE::BULLET;
}

bool Bullet::FixedUpdate(float time)
{
	this->lastPosition = this->position;
	this->position += this->velocity * time;

	float gravityAmt = 9.8f * 300 / velocity.y;

	velocity += Vector2D(0.0f, gravityAmt);

	collision.Update(this->position);
	MakeTrail();

	return true;
}

bool Bullet::Update()
{ 
	bool IsCollision = Raycast(lastPosition.x, lastPosition.y, position.x, position.y);

	if (IsCollision)
	{
		Explode(15);
	}
	else
	{
		if (!position.isValid())
			this->DeleteSelf();
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
			if (IsValidPos(x, y)) // 유효한 좌표?
			{
				float length = ((x - position.x) * (x - position.x) + (y - position.y) * (y - position.y));
				float r = radius * radius;

				if (length <= r)
				{
					if (map->IsPixelSolid(x, y))
					{
						map->RemoveStaticPixel(x, y);

						/* 동적 픽셀 생성 */

						Dynamic_Pixel *pixel = (Dynamic_Pixel*)ObjectPool::GetInstance()->GetGameObject(OBJECT_TYPE::DYNAMIC_PIXEL);

						pixel->SetPosition(Vector2D(x, y));
						pixel->SetSize(Vector2D(3, 3));

						float distanceRate = 1 - length / r;
						float speed = 300 * distanceRate;

						float xDiff = x - position.x;
						float yDiff = y - position.y;

						srand((unsigned)time(nullptr));
						float velX = speed * (xDiff + (rand() % 20 - 10));
						float velY = speed * (yDiff + (rand() % 20 - 10));

						pixel->velocity = Vector2D(velX, velY);

						string str = "pixel";

						Scene *scene = Game::GetInstance()->GetScene();

						bool success = scene->AddGameObject(pixel);

						if (success)
						{
							Physics::GetInstance()->AddObject(pixel);
						}
					}
				}
			}
		}
	}

	this->DeleteSelf();

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

	Vector2D sizeVector = GetSize();

	float left = this->position.x - sizeVector.x;
	float top = this->position.y - sizeVector.y;
	float right = this->position.x + sizeVector.x;
	float bottom = this->position.y + sizeVector.y;

	Rectangle(hdc, left, top, right, bottom);

	SelectObject(hdc, OldPen);
	DeleteObject(MyPen);
	SelectObject(hdc, OldBrush);
	DeleteObject(MyBrush);

	this->collision.Draw(hWnd, hdc);
}

void Bullet::MakeTrail()
{
	if (this->isActive)
	{
		BulletTrailObject* particleObj = (BulletTrailObject*)ObjectPool::GetInstance()->GetGameObject(OBJECT_TYPE::PARTICLE);

		particleObj->position = this->position;
		particleObj->Init();

		ParticleManager::GetInstance()->AddObject(particleObj);
	}
}