#include "Menu.h"
#include "Game.h"

Menu::Menu()
{
	optionValues[VELOCITY] = 180;
	optionValues[ACCELERATION] = 150;
	optionValues[SEPERATION_WEIGHT] = 200;
	optionValues[COHESION_WEIGHT] = 100;
	optionValues[ALIGNMENT_WEIGHT] = 100;
	mSelectedValue = 0;
	draw = true;
}

Menu::~Menu() {}

void Menu::prevOption()
{
	mSelectedValue++;
	if (mSelectedValue >= 5)
		mSelectedValue = 0;
	std::cout << "Setting value to: " + std::to_string((int)mSelectedValue) << std::endl;
}

void Menu::nextOption()
{
	mSelectedValue--;
	if (mSelectedValue < 0)
		mSelectedValue = 4;
	std::cout << "Setting value to: " + std::to_string((int)mSelectedValue) << std::endl;
}

void Menu::incrementSelected(const bool decrement)
{
	int direction = 1;
	if (decrement)
		direction = -1;
	switch (mSelectedValue)
	{
	case VELOCITY:
		optionValues[VELOCITY] += direction * 0.2f;
		for (int i = 0; i < gpGame->getUnitTotal(); i++)
		{
			gpGame->getManagedUnit(i)->setMaxVelocity(optionValues[VELOCITY]);
		}
		break;
	case ACCELERATION:
		optionValues[ACCELERATION] += direction * 0.2f;
		for (int i = 0; i < gpGame->getUnitTotal(); i++)
		{
			gpGame->getManagedUnit(i)->setMaxAcceleration(optionValues[ACCELERATION]);
		}
		break;
	case COHESION_WEIGHT:
		optionValues[COHESION_WEIGHT] += direction * 20;
		gpGame->setCohesionWeight(optionValues[COHESION_WEIGHT]);
		break;
	case SEPERATION_WEIGHT:
		optionValues[SEPERATION_WEIGHT] += direction * 20;
		gpGame->setSeperationWeight(optionValues[SEPERATION_WEIGHT]);
		break;
	case ALIGNMENT_WEIGHT:
		optionValues[ALIGNMENT_WEIGHT] += direction * 20;
		gpGame->setAlignmentWeight(optionValues[ALIGNMENT_WEIGHT]);
		break;
	}
}

void Menu::decrementSelected()
{
	incrementSelected(true);
}

void Menu::toggleDraw()
{
	draw = !draw;
}