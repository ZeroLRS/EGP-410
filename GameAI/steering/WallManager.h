#ifndef _WALLMANAGER_H
#define _WALLMANAGER_H

#include "Wall.h"
#include "Trackable.h"
#include <vector>

class WallManager : public Trackable
{
public:
	WallManager();
	~WallManager();

	int getWallCount();
	Wall* getWall(int index);
	void addWall(Wall* wall);
	void removeWall(int index);
	void clearWalls();

private:
	std::vector<Wall*> mWalls;
};

#endif