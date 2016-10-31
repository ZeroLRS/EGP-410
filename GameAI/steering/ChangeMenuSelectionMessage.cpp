#include "Game.h"
#include "GameMessageManager.h"
#include "ChangeMenuSelectionMessage.h"
#include "Menu.h"

ChangeMenuSelectionMessage::ChangeMenuSelectionMessage(const int direction)
	:GameMessage(CHANGE_MENU_SELECTION_MESSAGE)
	, mDirection(direction)
{
}

ChangeMenuSelectionMessage::~ChangeMenuSelectionMessage()
{
}

void ChangeMenuSelectionMessage::process()
{
	if (mDirection == 1)
	{
		gpGame->getMenu()->nextOption();
	}
	else if (mDirection == -1)
	{
		gpGame->getMenu()->prevOption();
	}
}

