#include "Menu.h"
#include "Game.h"

Menu::Menu()
{
	optionValues[0] = 180;
	optionValues[1] = 150;
	optionValues[2] = 100;
	mSelectedValue = 2;
	draw = true;
}

Menu::~Menu() {}

void Menu::nextOption()
{
	mSelectedValue++;
	if (mSelectedValue >= 3)
		mSelectedValue = 0;
	std::cout << "Setting value to: " + std::to_string((int)mSelectedValue) << std::endl;
}

void Menu::prevOption()
{
	mSelectedValue--;
	if (mSelectedValue < 0)
		mSelectedValue = 2;
	std::cout << "Setting value to: " + std::to_string((int)mSelectedValue) << std::endl;
}

void Menu::incrementSelected()
{
	switch (mSelectedValue)
	{
	case VELOCITY:
		optionValues[VELOCITY] += 0.2f;
		for (int i = 0; i < gpGame->getUnitTotal(); i++)
		{
			gpGame->getManagedUnit(i)->setMaxVelocity(optionValues[VELOCITY]);
		}
		break;
	case VISION_RADIUS:
		optionValues[VISION_RADIUS] += 10;
		gpGame->setUnitVisionRadius(optionValues[VISION_RADIUS]);
		break;
	case ACCELERATION:
		optionValues[ACCELERATION] += 0.2f;
		for (int i = 0; i < gpGame->getUnitTotal(); i++)
		{
			gpGame->getManagedUnit(i)->setMaxAcceleration(optionValues[ACCELERATION]);
		}
		break;
	/*case FRAME_RATE:
		optionValues[FRAME_RATE] += 33;
		gpGame->updateLoopTarget(optionValues[FRAME_RATE]);*/
	}
}

void Menu::decrementSelected()
{
	switch (mSelectedValue)
	{
	case VELOCITY:
		optionValues[VELOCITY] -= 0.2f;
		for (int i = 0; i < gpGame->getUnitTotal(); i++)
		{
			gpGame->getManagedUnit(i)->setMaxVelocity(optionValues[VELOCITY]);
		}
		break;
	case VISION_RADIUS:
		optionValues[VISION_RADIUS] -= 10;
		gpGame->setUnitVisionRadius(optionValues[VISION_RADIUS]);
		break;
	case ACCELERATION:
		optionValues[ACCELERATION] -= 0.2f;
		for (int i = 0; i < gpGame->getUnitTotal(); i++)
		{
			gpGame->getManagedUnit(i)->setMaxAcceleration(optionValues[ACCELERATION]);
		}
		break;
	/*case FRAME_RATE:
		optionValues[FRAME_RATE] -= 33;
		gpGame->updateLoopTarget(optionValues[FRAME_RATE]);*/
	}
}

void Menu::toggleDraw()
{
	draw = !draw;
}