#include "UnitManager.h"
#include "GameMessageManager.h"
#include "ExitGameMessage.h"
#include "Defines.h"
#include "Game.h"

UnitManager::UnitManager() { mUnitTotal = 0; }

UnitManager::~UnitManager()
{
	clearUnits();
}

void UnitManager::clearUnits()
{
	for (auto kv : mUnits)
	{
		delete kv.second;
	}

	mUnits.clear();
}

void UnitManager::pushUnit(KinematicUnit* newUnit, std::string key)
{
	if (!mUnits.count(key))
	{
		mUnits[key] = newUnit;
		mUnitTotal++;
	}
	else
		std::cout << "ERROR: Tried to insert a KinematicUnit* into mUnits, but the key is already taken!";
}

void UnitManager::deleteRandomUnit()
{
	//If the player is the only unit left, end the program
	if (mUnits.size() <= 1)
	{
		GameMessage* pMessage = new ExitGameMessage(true);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
		return;
	}

	int delIndex = rand() % mUnits.size();
	int count = 0;
	for (auto kv : mUnits)
	{
		if (delIndex == count) 
		{
			//Make sure we don't delete the player...
			//	Instead, recall the function.
			if (kv.first == "player")
			{
				deleteRandomUnit();
				return;
			}
			delete kv.second;
			mUnits.erase(kv.first);
			return;
		}
		++count;
	}
}

KinematicUnit* UnitManager::getUnit(std::string key)
{
	if (mUnits.count(key))
		return mUnits[key];
	else
	{
		std::cout << "ERROR: Tried to get a KinematicUnit* from mUnits, but the key is not taken! KEY: " << key << std::endl;
		return nullptr;
	}
}

void UnitManager::Update(float time)
{
	//Temporary updater while double buffering is fixed.
	for (auto kv : mUnits)
	{
		kv.second->update(time);
	}

	//Fix this mess later so that double buffering works properly.
	/*std::map<std::string, KinematicUnit> unitBuffer;
	//unitBuffer.insert(mUnits.begin(), mUnits.end);

	for (auto kv : mUnits)
	{
		unitBuffer[kv.first] = *kv.second;
	}

	for (auto kv : unitBuffer)
	{
		kv.second.update(time);
	}

	clearUnits();
	for (auto kv : unitBuffer)
	{
		mUnits[kv.first] = &kv.second;
	}*/
}

void UnitManager::Draw(GraphicsBuffer* pBuffer)
{
	for (auto kv : mUnits)
	{
		kv.second->draw(pBuffer);
	}
}