#include "ObjectPool.h"
#include "Object.h"
#include "Bullet.h"
#include "Pixel.h"
#include "BulletTrail.h"

Object* ObjectPool::TypeCheck(OBJECT_TYPE type)
{
	Object *obj = nullptr;

	switch (type)
	{
	case OBJECT_TYPE::OBJECT:
		obj = new Object();
		break;
	case OBJECT_TYPE::BULLET:
		obj = new Bullet();
		break;
	case OBJECT_TYPE::DYNAMIC_PIXEL:
		obj = new Dynamic_Pixel();
		break;
	case OBJECT_TYPE::PARTICLE:
		obj = new BulletTrailObject();
		break;
	default:
		obj = new Object();
		break;
	}

	return obj;
}

void ObjectPool::Create(OBJECT_TYPE type , int size)
{
	stack<Object*> objectList;

	for (int i = 0; i < size; i++)
	{
		Object *obj = this->TypeCheck(type);

		obj->isActive = false;
		objectList.push((Object*)obj);
	}

	if (&objectPools[type] != nullptr)
		objectPools[type] = objectList;
}

Object* ObjectPool::GetGameObject(OBJECT_TYPE type)
{
	Object *obj = nullptr;

	int count = objectPools[type].size();

	if (count > 0)
	{
		obj = objectPools[type].top();
		objectPools[type].pop();
		obj->isActive = true;
	}
	else
	{
		obj = this->TypeCheck(type);
		obj->isActive = true;
	}

	return obj;
}

void ObjectPool::Release(Object* gameObject)
{
	Object *obj = gameObject;
	OBJECT_TYPE type = obj->type;

	gameObject->isActive = false;
	objectPools[type].push(obj);
}

void ObjectPool::FreeAllObject()
{
	for (auto column = objectPools.begin(); column != objectPools.end(); column++)
	{
		auto row = (*column).second.top();
		while (row != nullptr)
		{
			(*column).second.pop();
			row = (*column).second.top();
		}
	}
}