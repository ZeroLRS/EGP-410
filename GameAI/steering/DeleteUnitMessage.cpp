#include "Game.h"
#include "GameMessageManager.h"
#include "DeleteUnitMessage.h"

DeleteUnitMessage::DeleteUnitMessage()
	:GameMessage(DELETE_UNIT_MESSAGE)
{
}

DeleteUnitMessage::~DeleteUnitMessage()
{
}

void DeleteUnitMessage::process()
{
	gpGame->deleteRandomUnit();
}