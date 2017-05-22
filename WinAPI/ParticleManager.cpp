#include "ParticleManager.h"
#include "ParticleObject.h"
#include "ObjectPool.h"

void ParticleManager::Update()
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
			Object* temp = (*iter);
			iter = objectList.erase(iter);
			ObjectPool::GetInstance()->Release(temp);
			continue;
		}
	}
}

void ParticleManager::Draw(HWND hWnd, HDC hdc)
{
	for (auto iter = objectList.begin(); iter != objectList.end(); iter++)
	{
		if ((*iter)->isActive) // Active == true
		{
			(*iter)->Draw(hWnd,hdc);
		}
	}
}

void ParticleManager::AddObject(ParticleObject* object)
{
	objectList.push_back(object);
}