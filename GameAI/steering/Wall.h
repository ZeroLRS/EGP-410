#ifndef _WALL_H
#define _WALL_H

#include "Trackable.h"
#include "Vector2D.h"

class Wall : public Trackable
{
public:
	Wall();
	Wall(Vector2D origin, Vector2D direction, float length);
	~Wall();

	const Vector2D getOrigin() { return mOrigin; };
	const Vector2D getDirection() { return mDirection; };
	const float getLength() { return mLength; };

private:
	Vector2D mOrigin, mDirection;
	float mLength;
};

#endif