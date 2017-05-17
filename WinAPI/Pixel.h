#pragma once
#include "Object.h"

// ���� �ȼ�
class Pixel
{
public:
	Vector2D position;

	Pixel():isSolid(false){};
	Pixel(Vector2D p_postion) :isSolid(false){ this->position = p_postion; }
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
	
	float stickness = 1500; // stickness ������ �ӵ��� �ȼ��� ����
	float bounceFriction = 0.85f; // ź����

	Dynamic_Pixel():Object(){};
	Dynamic_Pixel(Vector2D p_postion){ this->position = p_postion; this->lastPosition = lastPosition; }
	~Dynamic_Pixel(){};

	bool FixedUpdate(float time);
	bool Update();
private:
	bool Bounce();
	bool Stick();
};