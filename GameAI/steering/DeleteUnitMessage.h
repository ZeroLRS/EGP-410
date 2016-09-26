#ifndef _DELETEUNITMESSAGE_H
#define _DELETEUNITMESSAGE_H

#include "GameMessage.h"

class DeleteUnitMessage :public GameMessage
{
public:
	DeleteUnitMessage();
	~DeleteUnitMessage();

	void process();
};

#endif