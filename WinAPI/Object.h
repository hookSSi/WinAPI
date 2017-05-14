#pragma once
#include<Windows.h>
#include "Vector2D.h"
#include "Component.h"

class Object:public Component{
public:
	Vector2D position; // ��ġ
	Vector2D rotation; // ȸ��
	Vector2D scale; // ũ��
	bool isPhysics; // ���� ���� �޴� �� ����

	Object():isPhysics(true){};
	virtual ~Object(){};

	Object(Object &other);
	virtual const Object operator=(Object &other);

	const Vector2D& GetSize() const;
	const Vector2D& GetPivot() const;
	bool SetSize(Vector2D& size);
	bool SetPivot(Vector2D& pivot);

	virtual void Draw(HWND hWnd, HDC hdc){};
	virtual bool Update(){ return true; }; // ���� ������Ʈ ������Ʈ
private:
	Vector2D size;
	Vector2D pivot;
};