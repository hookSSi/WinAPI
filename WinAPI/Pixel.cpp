#include "Pixel.h"
#include "Map.h"
#include "Game.h"

Pixel::Pixel(const Pixel& other)
{
	this->position = other.position;
	this->isSolid = false;
}

bool Pixel::Update()
{

	return true;
}

bool Dynamic_Pixel::Update()
{
	Map map = Game::GetInstance()->GetMap();

	if (Raycast(map, lastPosition.x, lastPosition.y, position.x, position.y)._Myfirst._Val.isValid())
	{
		if (velocity.Magnitude() <= stickness)
		{
			this->Bounce();
		}
		else // 땅인지 확인하고 붙자
		{
			this->Stick();
		}
	}

	return true;
}

bool Dynamic_Pixel::FixedUpdate(float time)
{
	this->position = velocity * time;

	return true;
}

bool Dynamic_Pixel::Bounce()
{
	Map terrain = Game::GetInstance()->GetMap();

	Vector2D normal = terrain.GetNormal(position.x, position.y, 3);

	float projection = VectorMath::DotProduct(velocity, normal);

	velocity = velocity - (normal * projection * 2);

	return true;
}

bool Dynamic_Pixel::Stick()
{

	return true;
}