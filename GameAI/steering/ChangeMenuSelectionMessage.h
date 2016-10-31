#ifndef _CHANGEMENUSELECTION_H
#define _CHANGEMENUSELECTION_H

#include "GameMessage.h"

class ChangeMenuSelectionMessage : public GameMessage
{
public:
	ChangeMenuSelectionMessage(const int direction);
	~ChangeMenuSelectionMessage();

	void process();

private:
	int mDirection;
};

#endif