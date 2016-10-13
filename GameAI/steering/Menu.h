#ifndef _MENU_H
#define _MENU_H

#include "Trackable.h"
#include "UnitManager.h"
#include "GraphicsSystem.h"

class Menu : public Trackable
{
public:
	Menu();
	~Menu();

	bool drawMenu() { return draw; };

	void nextOption();
	void prevOption();
	void incrementSelected();
	void decrementSelected();
	void toggleDraw();
	float getOptionValue(int index) { return optionValues[index]; };

private:
	enum Options { VELOCITY, VISION_RADIUS, ACCELERATION };
	float optionValues[3];
	int mSelectedValue;
	bool draw;
};

#endif