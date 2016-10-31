#include "Game.h"
#include "GameMessageManager.h"
#include "SetMenuSelectionMessage.h"
#include "Menu.h"

SetMenuSelectionMessage::SetMenuSelectionMessage(const int item)
	:GameMessage(SET_MENU_SELECTION_MESSAGE)
	, mItem(item)
{
}

SetMenuSelectionMessage::~SetMenuSelectionMessage()
{
}

void SetMenuSelectionMessage::process()
{
	gpGame->getMenu()->setSelected(mItem);
}

