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

	enum Options { VELOCITY, ACCELERATION, COHESION_WEIGHT, SEPERATION_WEIGHT, ALIGNMENT_WEIGHT };

	bool drawMenu() { return draw; };

	void nextOption();
	void prevOption();
	void incrementSelected(const bool decrement = false);
	void decrementSelected();
	void toggleDraw();
	float getOptionValue(int index) { return optionValues[index]; };
	int getSelected() const { return mSelectedValue; };
	int setSelected(int selection) { mSelectedValue = selection; };
	std::string getOptionName(int option) { return mOptionNames[option]; };

private:
	float optionValues[5];
	std::string mOptionNames[5] = { "Velocity", "Acceleration", "Cohesion", "Seperation", "Alignment" };
	int mSelectedValue;
	bool draw;
};

#endif