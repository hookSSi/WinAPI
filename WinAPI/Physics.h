#pragma once
#include "stdafx.h"

class Physics{
public:
	float previousTime;
	float currentTime;
	static const int fixedDeltaTime = 16;
	float fixedDeltaTimeSeconds = (float)fixedDeltaTime / 1000.0f;
	int leftOverDeltaTime = 0;

	bool Update();

	Physics(){}
	~Physics(){}
};