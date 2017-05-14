#pragma once
#include<Windows.h>
#include "Vector2D.h"
#include "Component.h"

class Object:public Component{
public:
	Vector2D position; // 위치
	Vector2D rotation; // 회전
	Vector2D scale; // 크기
	bool isPhysics; // 물리 영향 받는 지 여부

	Object():isPhysics(true){};
	virtual ~Object(){};

	Object(Object &other);
	virtual const Object operator=(Object &other);

	const Vector2D& GetSize() const;
	const Vector2D& GetPivot() const;
	bool SetSize(Vector2D& size);
	bool SetPivot(Vector2D& pivot);

	virtual void Draw(HWND hWnd, HDC hdc){};
	virtual bool Update(){ return true; }; // 게임 오브젝트 업데이트
private:
	Vector2D size;
	Vector2D pivot;
};