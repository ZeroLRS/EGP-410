#include "UnitManager.h"

UnitManager::UnitManager() { }

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
		mUnits[key] = newUnit;
	else
		std::cout << "ERROR: Tried to insert a KinematicUnit* into mUnits, but the key is already taken!";
}

void UnitManager::deleteRandomUnit()
{
	int delIndex = rand() % mUnits.size();
	int count = 0;
	for (auto kv : mUnits)
	{
		if (delIndex == count)
		{
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