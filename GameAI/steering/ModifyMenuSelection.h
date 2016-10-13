#ifndef _MODIFYMENUSELECTION_H
#define _MOIDFYMENUSELECTION_H

#include "GameMessage.h"

class ModifyMenuSelection : public GameMessage
{
public:
	ModifyMenuSelection(const int direction);
	~ModifyMenuSelection();

	void process();

private:
	int mDirection;
};

#endif