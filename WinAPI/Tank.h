#pragma once
#include"stdafx.h"
#include"Object.h"
#include"builder.h"
#include"Collision.h"

// ��ũ Ŭ����
class Tank : public Object
{
public:
	Vector2D lastPosition;
	Vector2D velocity; // ��ũ �ӵ�

	Collision collision;

	Tank();
	virtual ~Tank(){};

	void SetVelocity(const Vector2D& p_velocity){ velocity = p_velocity; }
	void SetFireDelay(float value){ fireDelay = value; }
	void SetDashDelay(float value){ dashDelay = value; }

	virtual void Init(){ collision.radius = 15; } // ��ũ �ʱ�ȭ
	virtual void Draw(HWND hWnd, HDC hdc); // ��ũ�� �׸�
	virtual bool Update(); // ��ũ ������Ʈ
	virtual bool FixedUpdate(float time); // ��ũ ���� ������Ʈ

	// �̵�
	virtual void Move(Vector2D& p_direction);
	// �߻� ���� ����
	virtual void ControlDegree(float scale);
	// �߻�
	virtual void Fire(int p_master);
	// ����
	virtual void Jump(float p_scale);
	// �뽬
	virtual void Dash();
private:
	bool flip = { false };
	bool isGround = { false }; // ���� ����

	float fireDegree = 0; // ��ź �߻� ����

	float fireDelay = 2; // ��ź �߻� ������
	bool flag = { true };
	chrono::system_clock::time_point previousTime = { currentTime };

	Vector2D firePos; // ��ź �߻� ��ġ
	Vector2D fireDirection;

	float dashDelay = 0; // ��ũ �뽬 ������

	bool GroundChecking();
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
	virtual void BuildDashDelay() const { product->SetDashDelay(1); }
};