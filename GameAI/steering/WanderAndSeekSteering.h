#ifndef _WANDERANDSEEKSTEERING_H
#define _WANDERANDSEEKSTEERING_H

#include "Steering.h"
#include "KinematicUnit.h"

const float MAX_WANDER_ROTATION = 1.0f;

class WanderAndSeekSteering :public Steering
{
public:
	WanderAndSeekSteering(KinematicUnit* pMover, KinematicUnit* pTarget, int lookRadius, bool shouldFlee = false);
	~WanderAndSeekSteering() {};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
	KinematicUnit* mpTarget;
	int mLookRadius;
	bool mShouldFlee;
};

#endif