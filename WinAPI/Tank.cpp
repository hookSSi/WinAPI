#include "Tank.h"
#include "Game.h"
#include "Map.h"
#include "Bullet.h"
#include "ObjectPool.h"
#include "Physics.h"

Tank::Tank() : Object(), fireDelay(2), dashDelay(0){type = OBJECT_TYPE::TANK; velocity = Vector2D(1, 0); Init(); };

void Tank::Draw(HWND hWnd, HDC hdc)
{
	HBRUSH MyBrush, OldBrush;
	HPEN MyPen, OldPen;

	if (collision.isCollision)
	{
		MyBrush = (HBRUSH)CreateSolidBrush(RED_COLOR);
		OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);
		MyPen = CreatePen(PS_SOLID, 3, RED_COLOR);
		OldPen = (HPEN)SelectObject(hdc, MyPen);
	}
	else
	{
		MyBrush = (HBRUSH)CreateSolidBrush(WHITE_COLOR);
		OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);
		MyPen = CreatePen(PS_SOLID, 3, WHITE_COLOR);
		OldPen = (HPEN)SelectObject(hdc, MyPen);
	}

	

	// 몸체
	Vector2D sizeVec = GetSize();

	float left = this->position.x - sizeVec.x;
	float top = this->position.y - sizeVec.y;
	float right = this->position.x + sizeVec.x;
	float bottom = this->position.y + sizeVec.y;

	Rectangle(hdc, left, top, right, bottom);

	float gapTemp = sizeVec.y * 2;

	// 머리
	left = this->position.x - sizeVec.x / 2;
	top = top - gapTemp;
	right = this->position.x + sizeVec.x / 2;
	bottom = bottom - gapTemp;

	Rectangle(hdc, left, top, right, bottom);

	// 포신 
	MoveToEx(hdc, position.x, position.y - gapTemp, nullptr);

	fireDirection = Vector2D(cos(fireDegree * PI / 180.0f), sin(fireDegree * PI / 180.0f));
	Vector2D finalVector = fireDirection * gapTemp * 3.5f;

	if (!flip)
	{
		LineTo(hdc, position.x + finalVector.x, position.y - gapTemp - finalVector.y);
		firePos = Vector2D(position.x + finalVector.x, position.y - gapTemp - finalVector.y);
	}
	else
	{
		LineTo(hdc, position.x - finalVector.x, position.y - gapTemp - finalVector.y);
		firePos = Vector2D(position.x - finalVector.x, position.y - gapTemp - finalVector.y);
	}

	SelectObject(hdc, OldBrush);
	DeleteObject(MyBrush);

	//this->collision.Draw(hWnd, hdc);
}

bool Tank::Update()
{
	if (collision.isCollision)
	{
		collision.isActive = false;
		Game::GetInstance()->eventManager->onNotify(*this, EVENT::PLAYER_DEAD);
	}

	if (isActive)
	{
		return true;
	}
	return false;
}

bool Tank::FixedUpdate(float time)
{
	Vector2D sizeVec = GetSize();

	float left = this->position.x - sizeVec.x - 15;
	float top = this->position.y - sizeVec.y - 40;
	float right = this->position.x + sizeVec.x + 15;
	float bottom = this->position.y + sizeVec.y + 40;

	float gravityAmt = 9.80f;



	if (!IsValidPos(left, top) || !IsValidPos(right, bottom))
	{
		velocity.y = -velocity.y;
	}
	
	if (isGround)
	{
		if (velocity.y > 0)
			velocity.y = 0;
	}

	this->lastPosition = this->position;
	this->position += this->velocity * time;

	this->collision.Update(this->position, this->lastPosition);

	velocity.x = 0;

	velocity += Vector2D(0.0f, gravityAmt);

	isGround = GroundChecking();

	if (isGround)
		this->position = this->lastPosition;

	return true;
}

bool Tank::GroundChecking()
{
	Vector2D sizeVec = GetSize();

	float left = this->position.x - sizeVec.x;
	float right = this->position.x + sizeVec.x;
	float bottom = this->position.y + sizeVec.y;

	Map* terrain = Game::GetInstance()->GetMap();

	for (int x = left; x <= right; x++)
	{
		if (IsValidPos(x, bottom))
		{
			if (terrain->IsPixelSolid(x, bottom)) // 아래
			{
				this->isGround = true;
				return true;
			}
		}
	}

	return false;
}

void Tank::Move(Vector2D& p_velocity)
{
	if (p_velocity.x >= 0)
		flip = false;
	else
		flip = true;

	this->velocity.x = p_velocity.x;
}

void Tank::ControlDegree(float scale)
{
	float result = this->fireDegree + scale;

	if (result <= 90 && result >= 0)
	{
		this->fireDegree = result;
	}
}

void Tank::Fire(int p_master)
{
	currentTime = chrono::system_clock::now();

	std::chrono::duration<double> sec = currentTime - previousTime;

	if (sec.count() > fireDelay)
	{
		flag = true;
		previousTime = currentTime;
	}
	else
	{
		flag = false;
	}

	if (flag)
	{
		Bullet *bullet = (Bullet*)ObjectPool::GetInstance()->GetGameObject(OBJECT_TYPE::BULLET);

		bullet->SetSize(Vector2D(2, 2));
		bullet->collision.radius = 2;
		bullet->SetPosition(firePos);
		if (!flip)
		{
			bullet->velocity = Vector2D(fireDirection.x, -fireDirection.y) * 60;
		}
		else
			bullet->velocity = Vector2D(-fireDirection.x, -fireDirection.y) * 60;
		bullet->master = p_master;
		bullet->Init();

		Game::GetInstance()->AddGameObjet(bullet);
	}
}

void Tank::Jump(float p_scale)
{
	if (isGround)
	{
		this->velocity.y -= p_scale;
	}
}

void Tank::Dash()
{

}