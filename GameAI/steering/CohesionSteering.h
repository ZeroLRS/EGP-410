#ifndef _COHESIONSTEERING_H
#define _COHESIONSTEERING_H

#include "Steering.h"
#include "KinematicUnit.h"
#include "KinematicWanderSteering.h"

class CohesionSteering :public Steering
{
public:
	CohesionSteering(KinematicUnit* pMover);
	~CohesionSteering() {};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
};

#endif