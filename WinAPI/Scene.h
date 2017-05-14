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
	bool AddGameObject(string key, Object* value); // Object 추가
	bool DeleteGameObject(string key); // Object 삭제
	Object& GetGameObject(string key); // Object 리턴

	bool Update(); // 모든 Object Update
	bool Draw(HWND hWnd, HDC hdc); // 모든 Object 그리기
	Scene* self(){ return this; }
private:
	std::map<string, Object*> objectList;
};

// Scene 빌더
class Scene_Builder :public Builder < Scene >
{
public:
	Scene_Builder() : Builder<Scene>(){}
	~Scene_Builder(){}

	bool AddGameObject(string key, Object* value); // Object 추가
};