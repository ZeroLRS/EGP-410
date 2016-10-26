#include "SeperationSteering.h"
#include "Game.h"
#include "GraphicsSystem.h"

SeperationSteering::SeperationSteering(KinematicUnit* pMover)
	:mpMover(pMover)
{
	mApplyDirectly = false;
}

Steering* SeperationSteering::getSteering()
{
	mLookRadius = gpGame->getUnitVisionRadius();

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
			mLinear += unit->getPosition() - mpMover->getPosition();
		}
	}

	if (foundUnits == 0)
	{
		return this;
	}

	//Reverse the vector so we steer away from the neighbor instead of towards
	mLinear *= -1;
	//Average out all of the unit alignments
	mLinear /= foundUnits;
	mLinear.normalize();
	return this;
}
/*
 ______     _____      _____       _____      ____     _____    _____      ____
(_   _ \   (_   _)    / ___ \     (  __ \    / __ \   (  __ \  (  __ \    (    )
  ) (_) )    | |     / /   \_)     ) )_) )  / /  \ \   ) )_) )  ) )_) )   / /\ \
  \   _/     | |    ( (  ____     (  ___/  ( ()  () ) (  ___/  (  ___/   ( (__) )
  /  _ \     | |    ( ( (__  )     ) )     ( ()  () )  ) )      ) )       )    (
 _) (_) )   _| |__   \ \__/ /     ( (       \ \__/ /  ( (      ( (       /  /\  \
(______/   /_____(    \____/      /__\       \____/   /__\     /__\     /__(  )__\

*/