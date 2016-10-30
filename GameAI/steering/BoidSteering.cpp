#include "BoidSteering.h"
#include "Game.h"
#include "GraphicsSystem.h"
#include "Menu.h"

BoidSteering::BoidSteering(KinematicUnit* pMover)
	:mpMover(pMover)
{
	mApplyDirectly = false;

	mpSeperation = new SeperationSteering(pMover);
	mpCohesion = new CohesionSteering(pMover);
	mpAlignment = new AlignmentSteering(pMover);
}

BoidSteering::~BoidSteering()
{
	delete mpSeperation;
	delete mpCohesion;
	delete mpAlignment;
}

Steering* BoidSteering::getSteering()
{
	mLinear = Vector2D();
	
	Steering* seperVel = mpSeperation->getSteering();
	Steering* coheseVel = mpCohesion->getSteering();
	Steering* alignVel = mpAlignment->getSteering();

	//These can be move to a place easier to modify if needed.
	float seperWeight = gpGame->getMenu()->getOptionValue(Menu::SEPERATION_WEIGHT);
	float coheseWeight = gpGame->getMenu()->getOptionValue(Menu::COHESION_WEIGHT);
	float alignWeight = gpGame->getMenu()->getOptionValue(Menu::ALIGNMENT_WEIGHT);

	mLinear += seperVel->getLinear() * seperWeight + coheseVel->getLinear() * coheseWeight + alignVel->getLinear() * alignWeight;

	mLinear.normalize();
	mLinear *= mpMover->getMaxVelocity();
	return this;
}