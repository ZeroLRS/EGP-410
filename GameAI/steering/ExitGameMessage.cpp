#include "Game.h"
#include "GameMessageManager.h"
#include "ExitGameMessage.h"

ExitGameMessage::ExitGameMessage(const bool& exit)
	:GameMessage(EXIT_GAME_MESSAGE)
	, mExit(exit)
{
}

ExitGameMessage::~ExitGameMessage()
{
}

void ExitGameMessage::process()
{
	gpGame->setGameExit(mExit);
}

