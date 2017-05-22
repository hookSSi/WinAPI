#pragma once
#include "Singleton.h"
#include "stdafx.h"

class Object;

class ObjectPool : public Singleton<ObjectPool>
{
public:
	using ObjectPoolMap = map <OBJECT_TYPE, stack < Object* >>;
	ObjectPoolMap objectPools;

	ObjectPool(){ Create(OBJECT_TYPE::BULLET, 50); Create(OBJECT_TYPE::DYNAMIC_PIXEL, 1000); Create(OBJECT_TYPE::PARTICLE, 500); };
	~ObjectPool(){};

	void Create(OBJECT_TYPE type,int p_size);
	Object* GetGameObject(OBJECT_TYPE type);
	void Release(Object* gameObject);
	void FreeAllObject();
private:
	Object* TypeCheck(OBJECT_TYPE type);
};