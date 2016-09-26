#include "InputManager.h"
#include "Game.h"
#include "GraphicsSystem.h"
#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"
#include "ExitGameMessage.h"
#include "SpawnUnitMessage.h"
#include "DeleteUnitMessage.h"

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
		return;// true;
	}
	else
	{
		return;
	}
	return;
}

void InputManager::isADown()
{

	if (al_key_down(&current, ALLEGRO_KEY_A) == 1 && al_key_down(&prev, ALLEGRO_KEY_A) == 0)
	{
		GameMessage* pMessage = new SpawnUnitMessage("dynamicArrive");
		MESSAGE_MANAGER->addMessage(pMessage, 0);
		return;// true;
	}
	else
	{
		return;
	}
	return;
}

void InputManager::isSDown()
{

	if (al_key_down(&current, ALLEGRO_KEY_S) == 1 && al_key_down(&prev, ALLEGRO_KEY_S) == 0)
	{
		GameMessage* pMessage = new SpawnUnitMessage("dynamicSeek");
		MESSAGE_MANAGER->addMessage(pMessage, 0);
		return;// true;
	}
	else
	{
		return;
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
		return;// true;
	}
	else
	{
		return;
	}
	return;
}

void InputManager::update()
{
	al_get_keyboard_state(&current);

	isEscDown();
	isADown();
	isSDown();
	isDDown();
	mouseLBDown();

	prev = current;
}