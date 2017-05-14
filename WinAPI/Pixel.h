#pragma once
#include "Object.h"

class Pixel : public Object
{
public:
	Pixel() :leftOverTime(0.0f){};
	Pixel(Vector2D p_postion) : leftOverTime(0.0f){ this->position = p_postion; }
	Pixel(const Pixel& other);
	~Pixel(){};

	bool Update();
	void SetSolid(bool p_isSolid){ this->isActive = p_isSolid; }
	bool IsSolid(){ return this->isActive; }
private:
	float leftOverTime;
};