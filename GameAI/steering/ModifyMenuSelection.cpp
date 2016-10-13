#include "Game.h"
#include "GameMessageManager.h"
#include "ModifyMenuSelection.h"
#include "Menu.h"

ModifyMenuSelection::ModifyMenuSelection(const int direction)
	:GameMessage(MODIFY_MENU_SELECTION)
	, mDirection(direction)
{
}

ModifyMenuSelection::~ModifyMenuSelection()
{
}

void ModifyMenuSelection::process()
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

