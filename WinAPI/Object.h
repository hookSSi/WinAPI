#pragma once
#include "stdafx.h"
#include "Component.h"

class Object:public Component{
public:
	static unsigned int counter;

	OBJECT_TYPE type;

	Vector2D position; // ��ġ
	Vector2D rotation; // ȸ��
	Vector2D scale; // ũ��
	bool isPhysics; // ���� ���� �޴� �� ����

	Object() :isPhysics(false){ type = OBJECT_TYPE::OBJECT; counter++; };
	virtual ~Object(){ };

	Object(Object &other);
	virtual const Object operator=(Object &other);

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