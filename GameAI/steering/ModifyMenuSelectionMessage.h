#ifndef _MODIFYMENUSELECTION_H
#define _MOIDFYMENUSELECTION_H

#include "GameMessage.h"

class ModifyMenuSelectionMessage : public GameMessage
{
public:
	ModifyMenuSelectionMessage(const int direction);
	~ModifyMenuSelectionMessage();

	void process();

private:
	int mDirection;
};

#endif