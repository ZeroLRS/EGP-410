#include "Game.h"
#include "GameMessageManager.h"
#include "LoadDataMessage.h"

LoadDataMessage::LoadDataMessage()
	:GameMessage(LOAD_DATA_MESSAGE)
{
}

LoadDataMessage::~LoadDataMessage()
{
}

void LoadDataMessage::process()
{
	gpGame->loadGame();
}

