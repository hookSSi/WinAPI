#include "Pixel.h"
#include "Map.h"
#include "Game.h"

Pixel::Pixel(const Pixel& other) : isSolid(true)
{
	this->position = other.position;
}

bool Pixel::Update()
{
	return true;
}

void Dynamic_Pixel::Draw(HWND hWnd, HDC hdc)
{
	SetPixel(hdc, position.x, position.y, GREEN_COLOR);
}

bool Dynamic_Pixel::Update()
{
	bool IsCollision = Raycast(lastPosition.x, lastPosition.y, position.x, position.y);

	if (IsCollision)
	{
		if (velocity.Magnitude() > stickness)
		{
			this->Bounce();
		}
		else // 땅인지 확인하고 붙자
		{
			this->Stick();
		}
	}
	else
	{
		if (!IsValidPos(position.x, position.y))
		{
			this->DeleteSelf();
		}
	}

	return true;
}

bool Dynamic_Pixel::FixedUpdate(float time)
{
	this->lastPosition = position;
	this->position += velocity * time;

	velocity += Vector2D(0.0f, 9.8f);

	return true;
}

bool Dynamic_Pixel::Bounce()
{
	Map *terrain = Game::GetInstance()->GetMap();

	Vector2D normal = terrain->GetNormal(position.x, position.y, 3);

	float projection = VectorMath::DotProduct(velocity, normal);

	velocity = velocity - (normal * projection * 2);

	return true;
}

bool Dynamic_Pixel::Stick()
{
	Map *terrain = Game::GetInstance()->GetMap();

	terrain->AddStaticPixel(lastPosition.x, lastPosition.y);

	this->DeleteSelf();

	return true;
}