#ifndef _UNITMANAGER_H
#define _UNITMANAGER_H

#include "Trackable.h"
#include "KinematicUnit.h"

#include <map>
#include <vector>
#include <string>

class UnitManager : public Trackable
{
public:
	UnitManager();
	~UnitManager();

	void pushUnit(KinematicUnit* newUnit);
	void deleteRandomUnit();
	KinematicUnit* getUnit(int key);

	void Update( float time );
	void Draw( GraphicsBuffer* pBuffer );

	void createPlayer(KinematicUnit* player) { if (mpPlayer == nullptr) mpPlayer = player; };
	KinematicUnit* getPlayer() { return mpPlayer; };

	int getUnitTotal() { return mUnits.size(); };

private:
	void clearUnits();

	std::vector<KinematicUnit*> mUnits;
	KinematicUnit* mpPlayer;
};

#endif