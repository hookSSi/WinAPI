#include "Scene.h"
#include "Physics.h"

bool Scene::DeleteAllGameObject()
{
	for (auto iter = objectList.begin(); iter != objectList.end(); iter++)
	{
		delete(iter->second);
	}
	objectList.clear();
	return true;
}

bool Scene::AddGameObject(string key, Object* value)
{
	objectList[key] = value;

	return true;
}

bool Scene::DeleteGameObject(string key)
{
	objectList.erase(key);
	return true;
}

Object& Scene::GetGameObject(string key){ return *objectList[key]; }

bool Scene::Update()
{
	for (auto iter = objectList.begin(); iter != objectList.end(); iter++)
	{
		iter->second->Update();
	}

	return true;
}

bool Scene::Draw(HWND hWnd, HDC hdc)
{
	for (auto iter = objectList.begin(); iter != objectList.end(); iter++)
	{
		iter->second->Draw(hWnd, hdc);
	}

	return true;
}

bool Scene_Builder::AddGameObject(string key, Object* value)
{
	product->AddGameObject(key, value);
	return true;
}