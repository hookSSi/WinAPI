#include "ObjectPool.h"
#include "Object.h"
#include "Bullet.h"
#include "Pixel.h"

void ObjectPool::Create(OBJECT_TYPE type , int size)
{
	stack<Object*> objectList;

	for (int i = 0; i < size; i++)
	{
		Object *obj;

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
		default:
			obj = new Object();
			break;
		}

		obj->isActive = false;
		objectList.push((Object*)obj);
	}

	if (&objectPools[type] != nullptr)
		objectPools[type] = objectList;
}

Object* ObjectPool::GetGameObject(OBJECT_TYPE type)
{
	Object *obj;

	int count = objectPools[type].size();

	if (count < 5)
	{
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
		default:
			obj = new Object();
			break;
		}
		obj->isActive = true;
	}
	else
	{
		obj = objectPools[type].top();
		objectPools[type].pop();
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