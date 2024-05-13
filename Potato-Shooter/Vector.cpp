#include "Extension.h"


void Vector2Int::operator =(const Vector2Int& delta)
{
	x = delta.x;
	y = delta.y;
}

Vector2Int::operator Vector2() const
{
	return { (float)x, (float)y };
}

Vector2Int Vector2Int::operator -(const Vector2Int& delta)
{
	return { x - delta.x, y - delta.y };
}
Vector2Int Vector2Int::operator +(const Vector2Int& delta)
{
	return { x + delta.x,y + delta.y };
}

void Vector2Int::operator +=(const Vector2Int& delta)
{
	x += delta.x;
	y += delta.y;
}
void Vector2Int::operator -=(const Vector2Int& delta)
{
	x -= delta.x;
	y -= delta.y;
}

Vector2::Vector2(float x, float y) :x(x), y(y) {}

Vector2::operator Vector2Int() const
{
	return { (int)x, (int)y };
}

void Vector2::operator =(const Vector2& delta)
{
	x = delta.x;
	y = delta.y;
}

Vector2 Vector2::operator -(const Vector2& delta) const
{
	return { x - delta.x,y - delta.y };
}

Vector2 Vector2::operator +(const Vector2& delta) const
{
	return { x + delta.x,y + delta.y };
}
Vector2 Vector2::operator *(const float& ext) const
{
	return { x * ext, y * ext };
}

Vector2 Vector2::operator /(const float& ext) const
{
	return { x / ext, y / ext };
}

void Vector2::operator +=(const Vector2& delta)
{
	x += delta.x;
	y += delta.y;
}

void Vector2::operator -=(const Vector2& delta)
{
	x -= delta.x;
	y -= delta.y;
}

float Vector2::magnitude() const
{
	return sqrt(x * x + y * y);
}

Vector2 Vector2::normalized() const
{
	float magnitude = this->magnitude();

	if (magnitude > 0.0f)
	{
		return { x / magnitude, y / magnitude };
	}

	return { 0, 0 };
}
