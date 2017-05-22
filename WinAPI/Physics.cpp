#include "Physics.h"
#include "Object.h"
#include "Collision.h"
#include "Bullet.h"

void Physics::AddObject(Object* object)
{ 
	object_list.push_back(object);
}

bool Physics::Update()
{
	if (object_list.size() > 0)
	{
		currentTime = chrono::system_clock::now();

		std::chrono::duration<double> deltaTimeMS = (currentTime - this->previousTime);

		int timeStempAmt = (int)((deltaTimeMS.count() + this->leftOverDeltaTie) / this->fixedDeltaTime);

		timeStempAmt = (timeStempAmt < 1) ? timeStempAmt : 1;

		this->leftOverDeltaTie = deltaTimeMS.count() - (timeStempAmt * this->fixedDeltaTime);

		for (int i = 1; i <= timeStempAmt; i++)
		{
			for (auto iter = object_list.begin(); iter != object_list.end(); iter++)
			{
				if ((*iter)->isActive)
				{
					(*iter)->FixedUpdate(this->fixedDeltaTime);

					if ((*iter)->type == OBJECT_TYPE::BULLET) // collision 체크를 할거임
					{
						for (auto other = iter; other != object_list.end(); other++)
						{
							Bullet* bullet = (Bullet*)(*iter);
							Bullet* otherBullet = (Bullet*)(*other);
							bullet->collision.CollisionCheck(otherBullet->collision);
						}
					}
				}	
			}
		}

		this->previousTime = currentTime;
	}

	return true;
}

void Physics::DeleteObject(Object* object)
{
	for (auto iter = object_list.begin(); iter != object_list.end();)
	{
		if ((*iter) == object)
		{
			iter = object_list.erase(iter);
			return;
		}
		else
		{
			iter++;
		}
	}
}

void Physics::DeleteAllObject()
{
	object_list.clear();
}