#include "Game.h"
#include "Kinematic.h"
#include "KinematicUnit.h"
#include "Sprite.h"
#include "GraphicsSystem.h"
#include "Steering.h"
#include "KinematicSeekSteering.h"
#include "KinematicArriveSteering.h"
#include "KinematicWanderSteering.h"
#include "DynamicSeekSteering.h"
#include "DynamicArriveSteering.h"
#include "WanderAndSeekSteering.h"
#include "WallManager.h"
#include <math.h>

using namespace std;

Steering gNullSteering( gZeroVector2D, 0.0f );

KinematicUnit::KinematicUnit(Sprite *pSprite, const Vector2D &position, float orientation, const Vector2D &velocity, float rotationVel, float maxVelocity, float maxAcceleration)
:Kinematic( position, orientation, velocity, rotationVel )
,mpSprite(pSprite)
,mpCurrentSteering(NULL)
,mMaxVelocity(maxVelocity)
,mMaxAcceleration(maxAcceleration)
{
	mCollisionRadius = 10; //Just a test number, implement a better way to get this later
}

KinematicUnit::~KinematicUnit()
{
	delete mpCurrentSteering;
}

void KinematicUnit::draw( GraphicsBuffer* pBuffer )
{
	mpSprite->draw( *pBuffer, mPosition.getX(), mPosition.getY(), mOrientation );
}

void KinematicUnit::update(float time)
{
	//Calculate where we want to go.
	Steering* steering;
	if( mpCurrentSteering != NULL )
	{
		steering = mpCurrentSteering->getSteering();
	}
	else
	{
		steering = &gNullSteering;
	}

	if( steering->shouldApplyDirectly() )
	{
		//not stopped
		if( getVelocity().getLengthSquared() > MIN_VELOCITY_TO_TURN_SQUARED )
		{
			setVelocity( steering->getLinear() );
			setOrientation( steering->getAngular() );
		}

		//since we are applying the steering directly we don't want any rotational velocity
		setRotationalVelocity( 0.0f );
		steering->setAngular( 0.0f );
	}

	//Check if we've collided with anything.
	int wallCount = WALL_MANAGER->getWallCount();
	for (int i = 0; i < wallCount; i++)
	{
		Wall* currentWall = WALL_MANAGER->getWall(i);
		Vector2D lineOrigin = currentWall->getOrigin();
		Vector2D lineEnd = currentWall->getDirection() * currentWall->getLength();

		//This looks awful, make it look better before submitting.
		// Thanks to http://mathworld.wolfram.com/Point-LineDistance2-Dimensional.html for the help
		float distance = ((lineEnd.getX() - lineOrigin.getX()) * (lineOrigin.getY() - mPosition.getY())) -
			((lineOrigin.getX() - mPosition.getX()) * (lineEnd.getY() - lineOrigin.getY()));

		distance /= std::sqrt((lineEnd.getX() - lineOrigin.getX()) * (lineEnd.getX() - lineOrigin.getX()) +
			(lineEnd.getY() - lineOrigin.getY()) * (lineEnd.getY() - lineOrigin.getY()));

		//If they are colliding
		if (std::abs(distance) < mCollisionRadius)
		{
			int dirSide = distance > 0 ? 1 : -1;
			float dirX = currentWall->getDirection().getY() * dirSide;
			float dirY = currentWall->getDirection().getX();
			Vector2D newDirection(dirX, dirY);
			newDirection.normalize();
			mVelocity = newDirection * mMaxVelocity;
		}
	}

	//move the unit using current velocities
	Kinematic::update( time );
	//calculate new velocities
	calcNewVelocities( *steering, time, mMaxVelocity, 25.0f );
	//move to oposite side of screen if we are off
	GRAPHICS_SYSTEM->wrapCoordinates( mPosition );

	//set the orientation to match the direction of travel
	setNewOrientation();
}

//private - deletes old Steering before setting
void KinematicUnit::setSteering( Steering* pSteering )
{
	delete mpCurrentSteering;
	mpCurrentSteering = pSteering;
}

void KinematicUnit::setNewOrientation()
{ 
	mOrientation = getOrientationFromVelocity( mOrientation, mVelocity ); 
}

void KinematicUnit::seek(const Vector2D &target)
{
	KinematicSeekSteering* pSeekSteering = new KinematicSeekSteering( this, target );
	setSteering( pSeekSteering );
}

void KinematicUnit::arrive(const Vector2D &target)
{
	KinematicArriveSteering* pArriveSteering = new KinematicArriveSteering( this, target );
	setSteering( pArriveSteering );
}

void KinematicUnit::wander()
{
	KinematicWanderSteering* pWanderSteering = new KinematicWanderSteering( this );
	setSteering( pWanderSteering );
}

void KinematicUnit::dynamicSeek( KinematicUnit* pTarget )
{
	DynamicSeekSteering* pDynamicSeekSteering = new DynamicSeekSteering( this, gpGame->getPlayerUnit() );
	setSteering( pDynamicSeekSteering );
}

void KinematicUnit::dynamicFlee( KinematicUnit* pTarget )
{
	DynamicSeekSteering* pDynamicSeekSteering = new DynamicSeekSteering( this, gpGame->getPlayerUnit(), true );
	setSteering( pDynamicSeekSteering );
}

void KinematicUnit::dynamicArrive( KinematicUnit* pTarget )
{
	DynamicArriveSteering* pDynamicArriveSteering = new DynamicArriveSteering( this, gpGame->getPlayerUnit());
	setSteering( pDynamicArriveSteering );
}

void KinematicUnit::wanderAndFlee(KinematicUnit* pTarget)
{
	WanderAndSeekSteering* pWanderAndSeekSteering = new WanderAndSeekSteering(this, gpGame->getPlayerUnit(), true);
	setSteering(pWanderAndSeekSteering);
}

void KinematicUnit::wanderAndSeek(KinematicUnit* pTarget)
{
	WanderAndSeekSteering* pWanderAndSeekSteering = new WanderAndSeekSteering(this, gpGame->getPlayerUnit());
	setSteering(pWanderAndSeekSteering);
}

