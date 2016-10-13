#ifndef _CHANGEMENUSELECTION_H
#define _CHANGEMENUSELECTION_H

#include "GameMessage.h"

class ChangeMenuSelection : public GameMessage
{
public:
	ChangeMenuSelection(const int direction);
	~ChangeMenuSelection();

	void process();

private:
	int mDirection;
};

#endif