#include "Game.h"
#include "GameMessageManager.h"
#include "ModifyMenuSelectionMessage.h"
#include "Menu.h"

ModifyMenuSelectionMessage::ModifyMenuSelectionMessage(const int direction)
	:GameMessage(MODIFY_MENU_SELECTION_MESSAGE)
	, mDirection(direction)
{
}

ModifyMenuSelectionMessage::~ModifyMenuSelectionMessage()
{
}

void ModifyMenuSelectionMessage::process()
{
	if (mDirection == 1)
	{
		gpGame->getMenu()->incrementSelected();
	}
	else if (mDirection == -1)
	{
		gpGame->getMenu()->decrementSelected();
	}
}

