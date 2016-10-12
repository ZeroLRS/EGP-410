#include "WallManager.h"

WallManager::WallManager() {}

WallManager::~WallManager()
{
	clearWalls();
}

int WallManager::getWallCount()
{
	return mWalls.size();
}

Wall* WallManager::getWall(int index)
{
	return mWalls[index];
}

void WallManager::addWall(Wall* wall)
{
	mWalls.push_back(wall);
}

void WallManager::removeWall(int index)
{
	delete mWalls[index];
	mWalls.erase(mWalls.begin() + index);
}

void WallManager::clearWalls()
{
	for (auto w : mWalls)
	{
		delete w;
	}
	mWalls.clear();
}