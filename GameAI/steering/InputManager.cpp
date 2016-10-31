#include "InputManager.h"
#include "Game.h"
#include "GraphicsSystem.h"
#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"
#include "ExitGameMessage.h"
#include "SpawnUnitMessage.h"
#include "DeleteUnitMessage.h"
#include "ModifyMenuSelectionMessage.h"
#include "ChangeMenuSelectionMessage.h"
#include "SetMenuSelectionMessage.h"
#include "LoadDataMessage.h"
#include "SaveDataMessage.h"
#include "Menu.h"

InputManager::InputManager()
{
	
}

InputManager::~InputManager()
{
	delete mpMouse;
	//delete current;
	//delete prev;
}

void InputManager::mouseLBDown()
{
	al_get_mouse_state(mpMouse);
	bool lmbPressed = mpMouse->buttons & 1;
	if (lmbPressed && down)
	{
		return;
	}
	if (lmbPressed && !down)
	{
		down = true;
		Vector2D pos(mpMouse->x, mpMouse->y);
		GameMessage* pMessage = new PlayerMoveToMessage(pos);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
		return;
	}
	if (!lmbPressed)
	{
		down = false;
		return;
	}
}

Vector2D InputManager::getMousePos()
{
	al_get_mouse_state(mpMouse);
	return(Vector2D(mpMouse->x, mpMouse->y));
}

void InputManager::init()
{
	al_install_mouse();
	al_install_keyboard();
	if (!al_hide_mouse_cursor(GRAPHICS_SYSTEM->getDisplay()))
	{
		printf("Mouse cursor not able to be hidden!\n");
	}
	down = false;
	keyDown = false;
	mpMouse = new ALLEGRO_MOUSE_STATE;
	al_get_keyboard_state(&prev);
}

void InputManager::isEscDown()
{

	if (al_key_down(&current, ALLEGRO_KEY_ESCAPE) == 1 && al_key_down(&prev, ALLEGRO_KEY_ESCAPE) == 0)
	{
		GameMessage* pMessage = new ExitGameMessage(true);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
	return;
}

void InputManager::isADown()
{

	if (al_key_down(&current, ALLEGRO_KEY_A) == 1 && al_key_down(&prev, ALLEGRO_KEY_A) == 0)
	{
		GameMessage* pMessage = new SetMenuSelectionMessage(Menu::ALIGNMENT_WEIGHT);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
	return;
}

void InputManager::isCDown()
{

	if (al_key_down(&current, ALLEGRO_KEY_C) == 1 && al_key_down(&prev, ALLEGRO_KEY_C) == 0)
	{
		GameMessage* pMessage = new SetMenuSelectionMessage(Menu::COHESION_WEIGHT);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
	return;
}

void InputManager::isSDown()
{
	if (al_key_down(&current, ALLEGRO_KEY_S) == 1 && al_key_down(&prev, ALLEGRO_KEY_S) == 0)
	{
		GameMessage* pMessage = new SetMenuSelectionMessage(Menu::SEPERATION_WEIGHT);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
	return;
}

void InputManager::isIDown()
{

	if (al_key_down(&current, ALLEGRO_KEY_I) == 1 && al_key_down(&prev, ALLEGRO_KEY_I) == 0)
	{
		for (int i = 0; i < 5; i++)
		{
			GameMessage* pMessage = new SpawnUnitMessage("boid");
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}
	}
	return;
}

void InputManager::isDDown()
{
	ALLEGRO_KEYBOARD_STATE current;
	al_get_keyboard_state(&current);

	if (al_key_down(&current, ALLEGRO_KEY_D) == 1 && al_key_down(&prev, ALLEGRO_KEY_D) == 0)
	{
		GameMessage* pMessage = new DeleteUnitMessage();
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	return;
}

void InputManager::isPlusDown()
{
	ALLEGRO_KEYBOARD_STATE current;
	al_get_keyboard_state(&current);

	if (al_key_down(&current, ALLEGRO_KEY_EQUALS) == 1 && al_key_down(&prev, ALLEGRO_KEY_EQUALS) == 0)
	{
		GameMessage* pMessage = new ModifyMenuSelectionMessage(1);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	return;
}

void InputManager::isMinusDown()
{
	ALLEGRO_KEYBOARD_STATE current;
	al_get_keyboard_state(&current);

	if (al_key_down(&current, ALLEGRO_KEY_MINUS) == 1 && al_key_down(&prev, ALLEGRO_KEY_MINUS) == 0)
	{
		GameMessage* pMessage = new ModifyMenuSelectionMessage(-1);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
	return;
}

void InputManager::isUpArrowDown()
{
	ALLEGRO_KEYBOARD_STATE current;
	al_get_keyboard_state(&current);

	if (al_key_down(&current, ALLEGRO_KEY_UP) == 1 && al_key_down(&prev, ALLEGRO_KEY_UP) == 0)
	{
		GameMessage* pMessage = new ChangeMenuSelectionMessage(1);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
	return;
}

void InputManager::isDownArrowDown()
{
	ALLEGRO_KEYBOARD_STATE current;
	al_get_keyboard_state(&current);

	if (al_key_down(&current, ALLEGRO_KEY_DOWN) == 1 && al_key_down(&prev, ALLEGRO_KEY_DOWN) == 0)
	{
		GameMessage* pMessage = new ChangeMenuSelectionMessage(-1);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
	return;
}

void InputManager::isCtrlSDown()
{
	ALLEGRO_KEYBOARD_STATE current;
	al_get_keyboard_state(&current);

	if (al_key_down(&current, ALLEGRO_KEY_S) == 1 && al_key_down(&prev, ALLEGRO_KEY_S) == 0 && al_key_down(&current, ALLEGRO_KEY_LCTRL) == 1)
	{
		GameMessage* pMessage = new SaveDataMessage();
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
	return;
}

void InputManager::isCtrlODown()
{
	ALLEGRO_KEYBOARD_STATE current;
	al_get_keyboard_state(&current);

	if (al_key_down(&current, ALLEGRO_KEY_O) == 1 && al_key_down(&prev, ALLEGRO_KEY_O) == 0 && al_key_down(&current, ALLEGRO_KEY_LCTRL) == 1)
	{
		GameMessage* pMessage = new LoadDataMessage();
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
	return;
}

void InputManager::update()
{
	al_get_keyboard_state(&current);

	isEscDown(); //Exit the game
	isADown(); //Select Alignment
	isCDown(); //Select Cohesion
	isSDown(); //Select Seperation
	isDDown(); //Delete a boid
	isIDown(); //Spawn five boids
	isPlusDown(); //Increment selection
	isMinusDown(); //Decrement selection
	isUpArrowDown(); //Change selection up
	isDownArrowDown(); //Change selection down
	isCtrlSDown(); //Save state to file
	isCtrlODown(); //Load state from file
	//mouseLBDown(); //Move player unit

	prev = current;
}