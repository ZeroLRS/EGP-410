#ifndef _UNITMANAGER_H
#define _UNITMANAGER_H

#include "Trackable.h"
#include "KinematicUnit.h"

#include <map>
#include <vector>

class UnitManager : public Trackable
{
public:
	UnitManager();
	~UnitManager();

	void pushUnit(KinematicUnit* newUnit, std::string key);
	void deleteRandomUnit();
	KinematicUnit* getUnit(std::string key);

	void Update( float time );
	void Draw( GraphicsBuffer* pBuffer );

private:
	void clearUnits();

	std::map<std::string, KinematicUnit*> mUnits;
};

#endif