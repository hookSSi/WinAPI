#include "Object.h"

inline Object::Object(Object &other)
{
	this->position = other.position;
	this->rotation = other.rotation;
	this->scale = other.scale;
	this->size = other.size;
	this->pivot = other.pivot;
}

const Object Object::operator=(Object& object){ Object temp; return temp; }

const Vector2D& Object::GetSize() const  { return this->size; } // Å©±â 2Dº¤ÅÍ¸¦ ¸®ÅÏÇÔ
const Vector2D& Object::GetPivot() const  { return this->pivot; } // ÇÇº¿ 2Dº¤ÅÍ¸¦ ¸®ÅÏÇÔ

bool Object::SetSize(Vector2D& size) { this->size = size; pivot = size / 2; return true; }
bool Object::SetPivot(Vector2D& pivot) { this->pivot = pivot; return true; }