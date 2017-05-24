#pragma once
#include<math.h>

class Vector2D
{
public:
	float x;
	float y;

	Vector2D() : x(0), y(0){}
	explicit Vector2D(int _x, int _y) : x(_x), y(_y){}
	explicit Vector2D(float _x, float _y) : x(_x), y(_y){}
	Vector2D(const Vector2D &other){ this->x = other.x; this->y = other.y; }

	const Vector2D operator=(const Vector2D &right);
	const Vector2D operator+(const Vector2D &right) const;
	const Vector2D operator+=(const Vector2D &right);
	const Vector2D operator-(const Vector2D &right) const;
	const Vector2D operator-=(const Vector2D &right);

	const Vector2D operator*(const Vector2D &right) const;
	const Vector2D operator*(const int right) const;
	const Vector2D operator*(const float right) const;

	const Vector2D operator/(const Vector2D &right) const;
	const Vector2D operator/(const int right) const;
	const Vector2D operator/(const float right) const;

	const bool operator==(const Vector2D &right) const;
	const bool operator!=(const Vector2D &right) const;

	const float Magnitude() const;
	const Vector2D Normal() const;

	bool isValid() const;

	~Vector2D(){};
};

namespace VectorMath{
	const float GetDistance(const Vector2D &start, const Vector2D &end);
	const float DotProduct(const Vector2D &first, const Vector2D &second);
}

inline const Vector2D Vector2D::operator=(const Vector2D &right)
{
	this->x = right.x;
	this->y = right.y;

	return *this;
}

inline const Vector2D Vector2D::operator+(const Vector2D &right) const
{
	Vector2D temp;
	temp.x = this->x + right.x;
	temp.y = this->y + right.y;
	return temp;
}

inline const Vector2D Vector2D::operator+=(const Vector2D &right)
{
	Vector2D temp;
	this->x += right.x;
	this->y += right.y;
	temp.x = this->x;
	temp.y = this->y;
	return temp;
}

inline const Vector2D Vector2D::operator-(const Vector2D &right) const
{
	Vector2D temp;
	temp.x = this->x - right.x;
	temp.y = this->y - right.y;
	return temp;
}

inline const Vector2D Vector2D::operator-=(const Vector2D &right)
{
	Vector2D temp;
	this->x -= right.x;
	this->y -= right.y;
	temp.x = this->x;
	temp.y = this->y;
	return temp;
}

inline const Vector2D Vector2D::operator*(const Vector2D &right) const
{
	Vector2D temp;
	temp.x = this->x * right.x;
	temp.y = this->y * right.y;
	return temp;
}

inline const Vector2D Vector2D::operator*(const int right) const
{
	Vector2D temp;
	temp.x = this->x * right;
	temp.y = this->y * right;
	return temp;
}

inline const Vector2D Vector2D::operator*(const float right) const
{
	Vector2D temp;
	temp.x = this->x * right;
	temp.y = this->y * right;
	return temp;
}

inline const Vector2D Vector2D::operator/(const Vector2D &right) const
{
	Vector2D temp;
	temp.x = this->x / right.x;
	temp.y = this->y / right.y;
	return temp;
}

inline const Vector2D Vector2D::operator/(const int right) const
{
	Vector2D temp;
	temp.x = this->x / right;
	temp.y = this->y / right;
	return temp;
}

inline const Vector2D Vector2D::operator/(const float right) const
{
	Vector2D temp;
	temp.x = this->x / right;
	temp.y = this->y / right;
	return temp;
}

inline const bool Vector2D::operator==(const Vector2D &right) const
{
	if (this->x == right.x && this->y == right.y)
		return true;
	else
		return false;
}

inline const bool Vector2D::operator!=(const Vector2D &right) const
{
	if (this->x != right.x || this->y != right.y)
		return true;
	else
		return false;
}

inline const float Vector2D::Magnitude() const
{
	if (this->x == 0 && this->y == 0)
	{
		return 0;
	}
	else
	{
		return sqrt(this->x * this->x + this->y * this->y);
	}	
}

inline 	const Vector2D Vector2D::Normal() const
{
	return (*this) / this->Magnitude();
}