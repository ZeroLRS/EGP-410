#include "Wall.h"

Wall::Wall()
{
	mOrigin = Vector2D(0, 0);
	mDirection = Vector2D(0, 0);
	mLength = 0;
}

Wall::Wall(Vector2D origin, Vector2D direction, float length)
{
	mOrigin = origin;
	mDirection = direction;
	mLength = length;
}

Wall::~Wall() {}