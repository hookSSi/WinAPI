#pragma once
#include "Object.h"
#include "Collision.h"


class Bullet : public Object
{
public:
	int master = { 1 };

	Collision collision;

	Vector2D lastPosition;
	Vector2D velocity;

	Bullet();
	Bullet(Vector2D& p_postion, Vector2D& p_velocity, int p_master) :master(p_master){ type = OBJECT_TYPE::BULLET; this->position = p_postion; this->lastPosition = p_postion; this->velocity = p_velocity; }
	~Bullet(){};

	void Init(){ collision.isCollision = false;collision.Update(this->position,this->lastPosition); }; // 초기화
	virtual void Draw(HWND hWnd, HDC hdc); // 랜더링
	bool FixedUpdate(float time); // 물리 업데이트
	bool Update(); // 업데이트

	bool SetPosition(Vector2D& pos){ this->position = pos; this->lastPosition = pos; return true; }
private:
	bool Explode(int radius, Vector2D collisionVec);
	void MakeTrail();
};