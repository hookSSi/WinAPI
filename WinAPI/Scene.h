#pragma once
#include "stdafx.h"
#include "builder.h"
#include "Object.h"

// Scene
class Scene
{
public:
	Scene(){};
	~Scene(){};
	bool DeleteAllGameObject();
	/* Object �߰� */
	bool AddGameObject(Object* value);

	bool Update(); // ��� Object Update
	bool Draw(HWND hWnd, HDC hdc); // ��� Object �׸���
	Scene* self(){ return this; }
private:
	std::list<Object*> objectList;
};

// Scene ����
class Scene_Builder :public Builder < Scene >
{
public:
	Scene_Builder() : Builder<Scene>(){}
	~Scene_Builder(){}

	bool AddGameObject(Object* value); // Object �߰�
};