#ifndef _SEPERATIONSTEERING_H
#define _SEPERATIONSTEERING_H

#include "Steering.h"
#include "KinematicUnit.h"
#include "KinematicWanderSteering.h"

class SeperationSteering :public Steering
{
public:
	SeperationSteering(KinematicUnit* pMover);
	~SeperationSteering() {};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
};

#endif