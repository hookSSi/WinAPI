#include "Scene.h"
#include "Physics.h"

bool Scene::DeleteAllGameObject()
{
	for (auto iter = objectList.begin(); iter != objectList.end(); iter++)
	{
		Object* temp = iter->second;
		Physics::GetInstance()->DeleteObject(temp);
		iter = objectList.erase(iter);
		delete temp;
	}

	return true;
}

bool Scene::AddGameObject(string& key, Object* value)
{
	if (objectList[key] != nullptr)
	{
		string buffer = key + to_string(objectList.size());

		objectList[buffer] = value;
	}
	else
		objectList[key] = value;

	return true;
}

bool Scene::DeleteGameObject(string& key)
{
	delete(objectList[key]);
	objectList.erase(key);
	return true;
}

Object& Scene::GetGameObject(string& key){ return *objectList[key]; }

bool Scene::Update()
{
	for (auto iter = objectList.begin(); iter != objectList.end(); iter++)
	{
		if (iter->second->isActive == false)
		{
			Object* temp = iter->second;
			Physics::GetInstance()->DeleteObject(temp);
			iter = objectList.erase(iter);
			delete temp;
			continue;
		}

		if (iter->second != nullptr)
		{
			iter->second->Update();
		}
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