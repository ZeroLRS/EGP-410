#include "WanderAndSeekSteering.h"
#include "Game.h"

WanderAndSeekSteering::WanderAndSeekSteering(KinematicUnit* pMover, KinematicUnit* pTarget, int lookRadius, bool shouldFlee = false)
	:mpMover(pMover)
	, mpTarget(pTarget)
	, mLookRadius(lookRadius)
	, mShouldFlee(shouldFlee)
{
	mApplyDirectly = true;
}

Steering* WanderAndSeekSteering::getSteering()
{
	//Get the distance to the target for determining if we should seek/flee or wander


	mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity();
	mAngular = mpMover->getOrientation() * (genRandomBinomial() * MAX_WANDER_ROTATION);
	return this;
}