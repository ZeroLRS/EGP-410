#include "CohesionSteering.h"
#include "Game.h"
#include "GraphicsSystem.h"

CohesionSteering::CohesionSteering(KinematicUnit* pMover)
	:mpMover(pMover)
{
	mApplyDirectly = false;
}

Steering* CohesionSteering::getSteering()
{
	mLookRadius = 75;// gpGame->getUnitVisionRadius();
	mLinear = Vector2D();

	//Keep track of the units we have found
	int foundUnits = 0;
	KinematicUnit* closestUnit;
	for (int i = 0; i < gpGame->getUnitTotal(); i++)
	{
		KinematicUnit* unit = gpGame->getManagedUnit(i);
		int distanceToUnit = getDistance(mpMover->getPosition(), unit->getPosition());

		//If the unit is close enough, try to align with it.
		if (distanceToUnit < (mLookRadius))
		{
			++foundUnits;
			mLinear += unit->getPosition();
		}
	}

	if (foundUnits == 0)
	{
		return this;
	}

	//Average out all of the unit locations
	mLinear /= foundUnits;
	mLinear -= mpMover->getPosition();
	mLinear.normalize();
	return this;
}