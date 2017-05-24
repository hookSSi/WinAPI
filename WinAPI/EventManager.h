#pragma once
#include "Observer.h"

class EventManager
{
public:
	bool flag = {false};
	EventManager(){};
	virtual ~EventManager(){};

	virtual void onNotify(const Tank& object, EVENT event);
private:
	void ScoreUp(int player);
};