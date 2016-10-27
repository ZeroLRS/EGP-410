#ifndef _BOIDSTEERING_H
#define _BOIDSTEERING_H


/*************************************************************************************
*  ______     _____      _____       _____      ____     _____    _____      ____    *
* (_   _ \   (_   _)    / ___ \     (  __ \    / __ \   (  __ \  (  __ \    (    )   *
*   ) (_) )    | |     / /   \_)     ) )_) )  / /  \ \   ) )_) )  ) )_) )   / /\ \   *
*   \   _/     | |    ( (  ____     (  ___/  ( ()  () ) (  ___/  (  ___/   ( (__) )  *
*   /  _ \     | |    ( ( (__  )     ) )     ( ()  () )  ) )      ) )       )    (   *
*  _) (_) )   _| |__   \ \__/ /     ( (       \ \__/ /  ( (      ( (       /  /\  \  *
* (______/   /_____(    \____/      /__\       \____/   /__\     /__\     /__(  )__\ *
*                                                                                    *
**************************************************************************************/

#include "Steering.h"
#include "KinematicUnit.h"
#include "KinematicWanderSteering.h"
#include "SeperationSteering.h"
#include "CohesionSteering.h"
#include "AlignmentSteering.h"

class BoidSteering :public Steering
{
public:
	BoidSteering(KinematicUnit* pMover);
	~BoidSteering();

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;

	SeperationSteering* mpSeperation;
	CohesionSteering* mpCohesion;
	AlignmentSteering* mpAlignment;
};

#endif