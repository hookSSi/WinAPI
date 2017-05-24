#include "Physics.h"
#include "Object.h"
#include "Collision.h"
#include "Bullet.h"
#include "Tank.h"
#include "Game.h"

void Physics::AddObject(Object* object)
{ 
	object_list.push_back(object);
}

bool Physics::Update()
{
	if (object_list.size() > 0 || (player1_tank != nullptr && player2_tank != nullptr))
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
				}	
			}
			if (player1_tank != nullptr && player2_tank != nullptr)
			{
				player1_tank->FixedUpdate(this->fixedDeltaTime);
				player2_tank->FixedUpdate(this->fixedDeltaTime);
			}
		}
		
		this->CollisionCheck();

		this->previousTime = currentTime;
	}

	return true;
}


// 탱크와 총알의 충돌을 어떻게 깔끔하게 처리할까?
void Physics::CollisionCheck()
{
	if (player1_tank != nullptr && player2_tank != nullptr)
	{
		// 플레이어 1
		if (player1_tank->collision.isActive)
		{
			for (auto iter = object_list.begin(); iter != object_list.end(); iter++)
			{
				if ((*iter)->type == OBJECT_TYPE::BULLET)
				{
					if ((*iter)->isActive)	// collision 체크를 할거임
					{
						Bullet* bullet = (Bullet*)(*iter);

						if (bullet->master == 2)
						{
							if (player1_tank->collision.CollisionCheck(&bullet->collision))
							{
								bullet->DeleteSelf();
								break;
							}
						}
					}
				}
			}
		}

		// 플레이어 2
		if (player2_tank->collision.isActive)
		{
			for (auto iter = object_list.begin(); iter != object_list.end(); iter++)
			{
				if ((*iter)->type == OBJECT_TYPE::BULLET)
				{
					if ((*iter)->isActive)	// collision 체크를 할거임
					{
						Bullet* bullet = (Bullet*)(*iter);

						if (bullet->master == 1)
						{
							if (player2_tank->collision.CollisionCheck(&bullet->collision))
							{
								bullet->DeleteSelf();
								break;
							}
						}
					}
				}
			}
		}
		
	}
}

void Physics::DeleteObject(Object* object)
{
	object_list.remove(object);
}

void Physics::DeleteAllObject()
{
	object_list.clear();
}