#include "WanderAndSeekSteering.h"
#include "Game.h"
#include "GraphicsSystem.h"

WanderAndSeekSteering::WanderAndSeekSteering(KinematicUnit* pMover, KinematicUnit* pTarget, bool shouldFlee)
	:mpMover(pMover)
	, mpTarget(pTarget)
	, mShouldFlee(shouldFlee)
{
	mLookRadius = gpGame->getUnitVisionRadius();
	mApplyDirectly = false;
	wanderTarget = Vector2D(0, 0);
}

Steering* WanderAndSeekSteering::getSteering()
{
	//Get the distance to the target for determining if we should seek/flee or wander
	float distance = getDistance(mpMover->getPosition(), mpTarget->getPosition());

	if (distance > mLookRadius) //If we aren't in the radius, we need to wander
	{
		if (wanderTarget == Vector2D(0, 0) || getDistance(mpMover->getPosition(), wanderTarget) < mLookRadius) //If we haven't generated it or we are too close to the wanderTarget, regenerate it
		{
			wanderTarget = Vector2D(genRandomFloat() * GRAPHICS_SYSTEM->getWidth(), genRandomFloat() * GRAPHICS_SYSTEM->getHeight());
		}
		//Seek the wandertarget
		mLinear = wanderTarget - mpMover->getPosition();

	}
	else //Seek/flee the target
	{
		if (!mShouldFlee)
		{
			mLinear = mpTarget->getPosition() - mpMover->getPosition();
		}
		else
		{
			//If we are fleeing, we should also wander a bit towards the wanderTarget.
			Vector2D linearFlee = mpMover->getPosition() - mpTarget->getPosition();
			mLinear += linearFlee;
			mLinear /= 2;
		}
	}
	
	//Avoid the closest unit
	int closestUnitDistance = -1;
	KinematicUnit* closestUnit;
	for (int i = 0; i < gpGame->getUnitTotal(); i++)
	{
		KinematicUnit* unit = gpGame->getManagedUnit(i);
		int distanceToUnit = getDistance(mpMover->getPosition(), unit->getPosition());

		if (distanceToUnit < (mLookRadius / 2))
		{
			if ((distanceToUnit < closestUnitDistance || closestUnitDistance == -1) && distanceToUnit > 0)
			{
				closestUnitDistance = distanceToUnit;
				closestUnit = unit;
			}
		}
	}

	if (closestUnitDistance >= 0)
	{
		//Flee the nearby unit and merge that direction with the already existing direction.
		Vector2D linearFlee = mpMover->getPosition() - closestUnit->getPosition();
		mLinear += linearFlee;
		mLinear /= 2;
	}

	mLinear.normalize();
	mLinear *= mpMover->getMaxVelocity();
	mAngular = 0;
	return this;
}