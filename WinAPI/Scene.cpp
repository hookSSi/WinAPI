#include "Scene.h"
#include "Physics.h"
#include "ObjectPool.h"

bool Scene::DeleteAllGameObject()
{
	Physics::GetInstance()->DeleteAllObject();

	for (auto iter = objectList.begin(); iter != objectList.end();)
	{
		if ((*iter)->type == OBJECT_TYPE::DYNAMIC_PIXEL)
		{
			Object* temp = (*iter);
			iter = objectList.erase(iter);
			ObjectPool::GetInstance()->Release(temp);
		}
		else if ((*iter)->type == OBJECT_TYPE::BULLET)
		{
			Object* temp = (*iter);
			iter = objectList.erase(iter);
			ObjectPool::GetInstance()->Release(temp);
		}
		else
		{
			Object* temp = (*iter);
			delete temp;
			iter = objectList.erase(iter);
		}
	}

	return true;
}

bool Scene::AddGameObject(Object* value)
{
	objectList.push_back(value);

	return true;
}

bool Scene::Update()
{
	for (auto iter = objectList.begin(); iter != objectList.end();)
	{
		if ((*iter)->isActive) // Active == true
		{
			(*iter)->Update();
			iter++;
		}
		else // Active == false
		{
			if ((*iter)->type == OBJECT_TYPE::DYNAMIC_PIXEL)
			{
				Object* temp = (*iter);
				Physics::GetInstance()->DeleteObject(temp);
				iter = objectList.erase(iter);
				ObjectPool::GetInstance()->Release(temp);
				continue;
			}
			else if ((*iter)->type == OBJECT_TYPE::BULLET)
			{
				Object* temp = (*iter);
				Physics::GetInstance()->DeleteObject(temp);
				iter = objectList.erase(iter);
				ObjectPool::GetInstance()->Release(temp);
				continue;
			}
		}
	}

	return true;
}

bool Scene::Draw(HWND hWnd, HDC hdc)
{
	for (auto iter = objectList.begin(); iter != objectList.end(); iter++)
	{
		if ((*iter)->isActive)
			(*iter)->Draw(hWnd, hdc);
	}

	return true;
}

bool Scene_Builder::AddGameObject(Object* value)
{
	product->AddGameObject(value);
	return true;
}