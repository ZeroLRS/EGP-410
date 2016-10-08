#include "UnitManager.h"
#include "GameMessageManager.h"
#include "ExitGameMessage.h"
#include <algorithm>
#include "Defines.h"
#include "Game.h"

UnitManager::UnitManager() { mpPlayer = nullptr; }

UnitManager::~UnitManager()
{
	clearUnits();
	if (mpPlayer != nullptr)
		delete mpPlayer;
}

void UnitManager::clearUnits()
{
	for (auto v : mUnits)
	{
		delete v;
	}

	mUnits.clear();
}

void UnitManager::pushUnit(KinematicUnit* newUnit)
{
	if (std::find(mUnits.begin(), mUnits.end(), newUnit) == mUnits.end())
	{
		mUnits.push_back(newUnit);
	}
	else
		std::cout << "ERROR: Tried to insert a KinematicUnit* into mUnits, but the key is already taken!";
}

void UnitManager::deleteRandomUnit()
{
	//If there are no units left, end the program
	if (mUnits.size() <= 0)
	{
		GameMessage* pMessage = new ExitGameMessage(true);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
		return;
	}

	int delIndex = rand() % mUnits.size();
	delete mUnits[delIndex];
	mUnits.erase(mUnits.begin() + delIndex);
}

KinematicUnit* UnitManager::getUnit(int key)
{
	if ((int) mUnits.size() >= key)
		return mUnits[key];
	else
	{
		std::cout << "ERROR: Tried to get a KinematicUnit* from mUnits, but the key is not valid! KEY: " << key << std::endl;
		return nullptr;
	}
}

void UnitManager::Update(float time)
{
	//Temporary updater while double buffering is fixed.
	for (auto v : mUnits)
	{
		v->update(time);
	}

	mpPlayer->update(time);

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
	for (auto v : mUnits)
	{
		v->draw(pBuffer);
	}
	mpPlayer->draw(pBuffer);
}