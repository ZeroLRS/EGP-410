#ifndef _WANDERANDSEEKSTEERING_H
#define _WANDERANDSEEKSTEERING_H

#include "Steering.h"
#include "KinematicUnit.h"
#include "KinematicWanderSteering.h"

class WanderAndSeekSteering :public Steering
{
public:
	WanderAndSeekSteering(KinematicUnit* pMover, KinematicUnit* pTarget, bool shouldFlee = false);
	~WanderAndSeekSteering() {};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
	KinematicUnit* mpTarget;
	Vector2D wanderTarget;
	bool mShouldFlee;
};

#endif