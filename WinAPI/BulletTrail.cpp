#include "BulletTrail.h"

void BulletTrailObject::Init()
{
	previousTime = chrono::system_clock::now();
	isActive = true;
	lifeTime = 3.0f;
}

void BulletTrailObject::Draw(HWND hWnd, HDC hdc)
{
	if (isActive)
	{
		SetPixel(hdc, position.x, position.y, WHITE_COLOR);
	}	
}

bool BulletTrailObject::Update()
{
	currentTime = chrono::system_clock::now();

	std::chrono::duration<double> sec = currentTime - previousTime;

	if (sec.count() >= lifeTime)
	{
		isActive = false;
		previousTime = currentTime;
	}

	return true;
}