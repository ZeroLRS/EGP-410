#ifndef _SPAWNUNITMESSAGE_H
#define _SPAWNUNITMESSAGE_H

#include "GameMessage.h"

class SpawnUnitMessage :public GameMessage
{
public:
	SpawnUnitMessage(const std::string& type);
	~SpawnUnitMessage();

	void process();

private:
	std::string mType;
};

#endif