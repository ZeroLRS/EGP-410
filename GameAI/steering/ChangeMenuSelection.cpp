#include "Game.h"
#include "GameMessageManager.h"
#include "ChangeMenuSelection.h"
#include "Menu.h"

ChangeMenuSelection::ChangeMenuSelection(const int direction)
	:GameMessage(CHANGE_MENU_SELECTION)
	, mDirection(direction)
{
}

ChangeMenuSelection::~ChangeMenuSelection()
{
}

void ChangeMenuSelection::process()
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

