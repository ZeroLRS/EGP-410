#ifndef _EXITGAMEMESSAGE_H
#define _EXITGAMEMESSAGE_H

#include "GameMessage.h"

class ExitGameMessage :public GameMessage
{
public:
	ExitGameMessage(const bool& exit);
	~ExitGameMessage();

	void process();

private:
	bool mExit;
};

#endif