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
	bool AddGameObject(string key, Object* value); // Object �߰�
	bool DeleteGameObject(string key); // Object ����
	Object& GetGameObject(string key); // Object ����

	bool Update(); // ��� Object Update
	bool Draw(HWND hWnd, HDC hdc); // ��� Object �׸���
	Scene* self(){ return this; }
private:
	std::map<string, Object*> objectList;
};

// Scene ����
class Scene_Builder :public Builder < Scene >
{
public:
	Scene_Builder() : Builder<Scene>(){}
	~Scene_Builder(){}

	bool AddGameObject(string key, Object* value); // Object �߰�
};