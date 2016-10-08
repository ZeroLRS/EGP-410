#include "Steering.h"
#include <math.h>

float Steering::getDistance(const Vector2D& v1, const Vector2D& v2)
{
	float x, y;

	x = v1.getX() - v2.getX();
	y = v1.getY() - v2.getY();

	x *= x;
	y *= y;

	return sqrt(x + y);
}