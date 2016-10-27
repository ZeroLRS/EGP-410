#include "Game.h"
#include "GameMessageManager.h"
#include "SpawnUnitMessage.h"
#include "KinematicUnit.h"
#include "SpriteManager.h"

SpawnUnitMessage::SpawnUnitMessage(const std::string& type)
	:GameMessage(SPAWN_UNIT_MESSAGE)
	, mType(type)
{
}

SpawnUnitMessage::~SpawnUnitMessage()
{
}

void SpawnUnitMessage::process()
{
	Sprite* enemySprite = gpGame->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID);
	KinematicUnit* playerUnit = gpGame->getPlayerUnit();

	Vector2D pos = playerUnit->getPosition();
	pos.setX(pos.getX() + 100);

	Vector2D vel(0.0f, 0.0f);

	KinematicUnit* pAIUnit = new KinematicUnit(enemySprite, pos, 1, vel, 0.0f, 180.0f, 100.0f);

	if (mType == "dynamicArrive")
		pAIUnit->dynamicArrive(playerUnit);
	else if (mType == "dynamicSeek")
		pAIUnit->dynamicSeek(playerUnit);
	else if (mType == "wanderAndSeek")
		pAIUnit->wanderAndSeek(playerUnit);
	else if (mType == "wanderAndFlee")
		pAIUnit->wanderAndFlee(playerUnit);
	else if (mType == "boid")
		pAIUnit->boid(playerUnit);
	else
	{
		std::cout << "ERROR: Could not create AI with type: " << mType << ". Deleting unit and returning." << std::endl;
		delete pAIUnit;
		return;
	}

	gpGame->pushManagedUnit(pAIUnit);
}

