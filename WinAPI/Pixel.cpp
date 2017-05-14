#include"Pixel.h"

Pixel::Pixel(const Pixel& other)
{
	this->position = other.position;
	this->rotation = other.rotation;
	this->isActive = other.isActive;
	this->isPhysics = other.isPhysics;
}

bool Pixel::Update()
{

	return true;
}