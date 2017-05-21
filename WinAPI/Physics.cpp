#include "Physics.h"
#include "Object.h"

bool Physics::Update()
{
	if (object_list.size() > 0)
	{
		this->currentTime = chrono::system_clock::now();

		std::chrono::duration<double> deltaTimeMS = (this->currentTime - this->previousTime);

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
		}

		this->previousTime = this->currentTime;
	}

	return true;
}

void Physics::DeleteObject(Object* object)
{
	for (auto iter = object_list.begin(); iter != object_list.end();)
	{
		if ((*iter)->isActive == false)
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