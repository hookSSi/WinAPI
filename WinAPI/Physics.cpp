#include "Physics.h"
#include "Object.h"

bool Physics::Update()
{
	this->currentTime = chrono::system_clock::now();

	float deltaTimeMS = (this->currentTime - this->previousTime).count();

	int timeStempAmt = (int)((deltaTimeMS + this->leftOverDeltaTie) / this->fixedDeltaTime);

	if (timeStempAmt == 0) // 0이 되어 멈추는 걸 방지
		timeStempAmt = 1;

	this->leftOverDeltaTie = deltaTimeMS - (timeStempAmt * this->fixedDeltaTime);

	float timeToUse = timeStempAmt * this->fixedDeltaTime;

	for (auto iter = object_list.begin(); iter != object_list.end(); iter++)
	{
		(*iter)->FixedUpdate(timeToUse);
	}

	return true;
}