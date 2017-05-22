#pragma once
#include "Object.h"

// ���� �ȼ�
class Pixel
{
public:
	Vector2D position;

	Pixel():isSolid(false){};
	Pixel(Vector2D& p_postion) :isSolid(false){ this->position = p_postion; }
	Pixel(const Pixel& other);
	~Pixel(){};

	bool Update();
	void SetSolid(bool p_isSolid){ this->isSolid = p_isSolid; }
	bool IsSolid(){ return this->isSolid; }
private:
	bool isSolid;
};

// ���� �ȼ�
class Dynamic_Pixel : public Object
{
public:
	Vector2D lastPosition;
	Vector2D velocity;
	float maxVelocity;
	
	float stickness; // stickness ������ �ӵ��� �ȼ��� ����
	float bounceFriction; // ź����

	Dynamic_Pixel() :Object(), stickness(500), bounceFriction(0.25f), maxVelocity(1000){ type = OBJECT_TYPE::DYNAMIC_PIXEL; };
	Dynamic_Pixel(Vector2D& p_postion) :Object(), stickness(500), bounceFriction(0.25f), maxVelocity(1000){ type = OBJECT_TYPE::DYNAMIC_PIXEL; this->position = p_postion; this->lastPosition = lastPosition; }
	~Dynamic_Pixel(){ };

	virtual void Draw(HWND hWnd, HDC hdc);
	bool FixedUpdate(float time);
	bool Update();

	bool SetPosition(Vector2D& pos){ this->position = pos; this->lastPosition = pos; return true; }
private:
	bool Bounce();
	bool Stick();
};