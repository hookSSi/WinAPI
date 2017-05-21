#pragma once
#include "Singleton.h"
#include "stdafx.h"

class Object;

class ObjectPool : public Singleton<ObjectPool>
{
public:
	using ObjectPoolMap = map <OBJECT_TYPE, stack < Object* >>;
	ObjectPoolMap objectPools;

	ObjectPool(){ Create(OBJECT_TYPE::BULLET, 20); Create(OBJECT_TYPE::DYNAMIC_PIXEL, (WIDTH * HEIGHT)/2); };
	~ObjectPool(){};

	void Create(OBJECT_TYPE type,int p_size);
	Object* GetGameObject(OBJECT_TYPE type);
	void Release(Object* gameObject);
private:

};