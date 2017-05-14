#pragma once
#include<Windows.h>
#include"Object.h"
#include"builder.h"

// ÅÊÅ© Å¬·¡½º
class Tank : public Object
{
public:
	Tank();
	virtual ~Tank(){};

	void SetVelocity(float value){ velocity = value; }
	void SetFireDelay(float value){ fireDelay = value; }
	void SetJumpDelay(float value){ jumpDelay = value; }
	void SetDashDelay(float value){ dashDelay = value; }
	void SetDirection(const Vector2D& direction){ this->direction = direction; }

	virtual void Draw(HWND hWnd, HDC hdc); // ÅÊÅ©¸¦ ±×¸²
	virtual bool Update(); // ÅÊÅ© ¾÷µ¥ÀÌÆ®

	// ÀÌµ¿
	virtual void Move();
	virtual void Move(Vector2D p_direction);
	// ¹ß»ç
	virtual void Fire();
	// Á¡ÇÁ
	virtual void Jump();
	// ´ë½¬
	virtual void Dash();
private:
	Vector2D direction;
	float velocity = 0;
	float fireDelay = 0;
	float jumpDelay = 0;
	float dashDelay = 0;
};

// ÅÊÅ© ºô´õ
class TankBuilder :public Builder<Tank>
{
public:
	TankBuilder() : Builder<Tank>(){}
	~TankBuilder(){}

	virtual void BuildVelocity() = 0;
	virtual void BuildFireDelay() = 0;
	virtual void BuildJumpDelay() = 0;
	virtual void BuildDashDelay() = 0;
};

// ³ë¸» ÅÊÅ© ºô´õ
class NormalTankBuilder : public TankBuilder
{
	NormalTankBuilder() : TankBuilder(){}
	~NormalTankBuilder(){}

	virtual void BuildVelocity() const { product->SetVelocity(1); }
	virtual void BuildFireDelay() const { product->SetFireDelay(1); }
	virtual void BuildJumpDelay() const { product->SetJumpDelay(1); }
	virtual void BuildDashDelay() const { product->SetDashDelay(1); }
};