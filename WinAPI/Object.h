#pragma once
#include "stdafx.h"
#include "Component.h"
#include "Collision.h"

class Object:public Component{
public:
	OBJECT_TYPE type;

	Vector2D position; // ��ġ

	Object(){ type = OBJECT_TYPE::OBJECT;};
	virtual ~Object(){ };

	const Vector2D& GetSize() const;
	const Vector2D& GetPivot() const;
	bool SetSize(Vector2D& size);
	bool SetPivot(Vector2D& pivot);

	virtual void Draw(HWND hWnd, HDC hdc){};
	virtual bool Update(){ return true; } // ���� ������Ʈ ������Ʈ
	virtual bool FixedUpdate(float time){ return true; }
private:
	Vector2D size;
	Vector2D pivot;
};