#include "Physics.h"
#include "Object.h"

bool Physics::Update()
{
	if (object_list.size() > 0)
	{
		this->currentTime = chrono::system_clock::now();

		std::chrono::duration<double> deltaTimeMS = (this->currentTime - this->previousTime);

		int timeStempAmt = (int)((deltaTimeMS.count() + this->leftOverDeltaTie) / this->fixedDeltaTime);

		if (timeStempAmt == 0) // 0이 되어 멈추는 걸 방지
			timeStempAmt = 1;

		this->leftOverDeltaTie = deltaTimeMS.count() - (timeStempAmt * this->fixedDeltaTime);

		float timeToUse = timeStempAmt * this->fixedDeltaTime;

	
		for (auto iter = object_list.begin(); iter != object_list.end(); iter++)
		{
			(*iter)->FixedUpdate(timeToUse);
		}

		this->previousTime = this->currentTime;
	}

	return true;
}

void Physics::DeleteObject(Object* object)
{
	for (auto iter = object_list.begin(); iter != object_list.end(); iter++)
	{
		if ((*iter)->isActive == false)
		{
			iter = object_list.erase(iter);
			return;
		}
	}
}