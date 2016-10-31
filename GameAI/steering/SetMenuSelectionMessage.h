#ifndef _SETMENUSELECTIONMESSAGE_H
#define _SETMENUSELECTIONMESSAGE_H

#include "GameMessage.h"

class SetMenuSelectionMessage : public GameMessage
{
public:
	SetMenuSelectionMessage(const int item);
	~SetMenuSelectionMessage();

	void process();

private:
	int mItem;
};

#endif