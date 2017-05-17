#include "Vector2D.h"
#include "stdafx.h"

const float VectorMath::GetDistance(const Vector2D &start, const Vector2D &end)
{
	float result = 0;

	result = Vector2D(start - end).Magnitude();

	return result;
}
const float VectorMath::DotProduct(const Vector2D &first, const Vector2D &second)
{
	float result = 0;

	result = first.x * second.x + first.y * second.y;

	return result;
}
bool Vector2D::isValid() const
{
	if (this->x < 0 || this->y < 0 || this->x > WIDTH || this->y > HEIGHT)
		return false;
	else
		return true;
}
