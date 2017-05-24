#pragma once
class Tank;

// ¿Ã∫•∆Æ
enum class EVENT
{
	PLAYER_DEAD
};

class Observer
{
public:
	Observer(){};
	virtual ~Observer() = 0;
	virtual void onNotify(const Tank& object, EVENT event);
};