#pragma once
#include<Windows.h>
#include"Object.h"
#include"builder.h"

// ��ũ Ŭ����
class Tank : public Object
{
public:
	Tank();
	virtual ~Tank(){};

	void SetVelocity(const Vector2D& p_velocity){ velocity = p_velocity; }
	void SetFireDelay(float value){ fireDelay = value; }
	void SetJumpDelay(float value){ jumpDelay = value; }
	void SetDashDelay(float value){ dashDelay = value; }

	virtual void Draw(HWND hWnd, HDC hdc); // ��ũ�� �׸�
	virtual bool Update(); // ��ũ ������Ʈ

	// �̵�
	virtual void Move();
	virtual void Move(Vector2D& p_direction);
	// �߻�
	virtual void Fire();
	// ����
	virtual void Jump();
	// �뽬
	virtual void Dash();
private:
	Vector2D velocity;
	float fireDelay = 0;
	float jumpDelay = 0;
	float dashDelay = 0;
};

// ��ũ ����
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

// �븻 ��ũ ����
class NormalTankBuilder : public TankBuilder
{
	NormalTankBuilder() : TankBuilder(){}
	~NormalTankBuilder(){}

	virtual void BuildVelocity() const { product->SetVelocity(Vector2D(1,1)); }
	virtual void BuildFireDelay() const { product->SetFireDelay(1); }
	virtual void BuildJumpDelay() const { product->SetJumpDelay(1); }
	virtual void BuildDashDelay() const { product->SetDashDelay(1); }
};