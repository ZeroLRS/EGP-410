#ifndef _ALIGNMENTSTEERING_H
#define _ALIGNMENTSTEERING_H

#include "Steering.h"
#include "KinematicUnit.h"
#include "KinematicWanderSteering.h"

class AlignmentSteering :public Steering
{
public:
	AlignmentSteering(KinematicUnit* pMover);
	~AlignmentSteering() {};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
};

#endif