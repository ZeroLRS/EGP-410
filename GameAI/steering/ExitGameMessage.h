#pragma once

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