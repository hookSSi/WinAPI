#pragma once
#include"stdafx.h"
#include"Object.h"
#include"builder.h"
#include"Collision.h"

// 탱크 클래스
class Tank : public Object
{
public:
	Vector2D lastPosition;
	Vector2D velocity; // 탱크 속도

	Collision collision;

	Tank();
	virtual ~Tank(){};

	void SetVelocity(const Vector2D& p_velocity){ velocity = p_velocity; }
	void SetFireDelay(float value){ fireDelay = value; }
	void SetDashDelay(float value){ dashDelay = value; }

	virtual void Init(){ collision.radius = 15; } // 탱크 초기화
	virtual void Draw(HWND hWnd, HDC hdc); // 탱크를 그림
	virtual bool Update(); // 탱크 업데이트
	virtual bool FixedUpdate(float time); // 탱크 물리 업데이트

	// 이동
	virtual void Move(Vector2D& p_direction);
	// 발사 각도 조절
	virtual void ControlDegree(float scale);
	// 발사
	virtual void Fire(int p_master);
	// 점프
	virtual void Jump(float p_scale);
	// 대쉬
	virtual void Dash();
private:
	bool flip = { false };
	bool isGround = { false }; // 땅에 있음

	float fireDegree = 0; // 포탄 발사 각도

	float fireDelay = 2; // 포탄 발사 딜레이
	bool flag = { true };
	chrono::system_clock::time_point previousTime = { currentTime };

	Vector2D firePos; // 포탄 발사 위치
	Vector2D fireDirection;

	float dashDelay = 0; // 탱크 대쉬 딜레이

	bool GroundChecking();
};

// 탱크 빌더
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

// 노말 탱크 빌더
class NormalTankBuilder : public TankBuilder
{
	NormalTankBuilder() : TankBuilder(){}
	~NormalTankBuilder(){}

	virtual void BuildVelocity() const { product->SetVelocity(Vector2D(1,1)); }
	virtual void BuildFireDelay() const { product->SetFireDelay(1); }
	virtual void BuildDashDelay() const { product->SetDashDelay(1); }
};