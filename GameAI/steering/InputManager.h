#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H

#include "allegro5\allegro.h"
#include "Trackable.h"
#include "Vector2D.h"
#include "Defines.h"

class InputManager : public Trackable
{
public:
	InputManager();
	~InputManager();
	Vector2D getMousePos();
	void update();

	void init();

private:
	ALLEGRO_MOUSE_STATE* mpMouse;
	ALLEGRO_KEYBOARD_STATE current, prev;
	void isEscDown();
	void isADown();
	void isCDown();
	void isSDown();
	void isDDown();
	void isIDown();
	void isPlusDown();
	void isMinusDown();
	void isUpArrowDown();
	void isDownArrowDown();
	void isCtrlODown();
	void isCtrlSDown();
	void mouseLBDown();
	bool down;
	bool keyDown;

};

#endif