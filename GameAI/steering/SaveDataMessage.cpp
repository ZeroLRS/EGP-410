#include "Game.h"
#include "GameMessageManager.h"
#include "SaveDataMessage.h"

SaveDataMessage::SaveDataMessage()
	:GameMessage(SAVE_DATA_MESSAGE)
{
}

SaveDataMessage::~SaveDataMessage()
{
}

void SaveDataMessage::process()
{
	gpGame->saveGame();
}

