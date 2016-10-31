#ifndef _GAME_H
#define _GAME_H

#include "Trackable.h"
#include "PerformanceTracker.h"
#include "Defines.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <string>
#include <time.h>
#include <stdlib.h>

#include "UnitManager.h"
#include "InputManager.h"
#include "WallManager.h"

class GraphicsSystem;
class GraphicsBuffer;
class GraphicsBufferManager;
class SpriteManager;
class KinematicUnit;
class GameMessageManager;
class Timer;
class Menu;

const IDType BACKGROUND_SPRITE_ID = 0;
const IDType PLAYER_ICON_SPRITE_ID = 1;
const IDType AI_ICON_SPRITE_ID = 2;

const float LOOP_TARGET_TIME = 33.3f;//how long should each frame of execution take? 30fps = 33.3ms/frame

class Game:public Trackable
{
public:
	Game();
	~Game();

	bool init();//returns true if no errors, false otherwise
	void cleanup();

	//game loop
	void beginLoop();
	void processLoop();
	bool endLoop();

	void saveGame();
	void loadGame();

	inline GraphicsSystem* getGraphicsSystem() const { return mpGraphicsSystem; };
	inline GraphicsBufferManager* getGraphicsBufferManager() const { return mpGraphicsBufferManager; };
	inline SpriteManager* getSpriteManager() const { return mpSpriteManager; };
	inline GameMessageManager* getMessageManager() { return mpMessageManager; };
	inline Timer* getMasterTimer() const { return mpMasterTimer; };
	inline double getCurrentTime() const { return mpMasterTimer->getElapsedTime(); };
	inline KinematicUnit* getManagedUnit(int key) const { return mpUnitManager->getUnit(key); };
	inline KinematicUnit* getPlayerUnit() const { return mpUnitManager->getPlayer(); };
	inline WallManager* getWallManager() const { return mpWallManager; };
	inline int getUnitTotal() const { return mpUnitManager->getUnitTotal(); };
	inline void pushManagedUnit(KinematicUnit* unit) { mpUnitManager->pushUnit(unit); };
	inline void deleteRandomUnit() { mpUnitManager->deleteRandomUnit(); };
	inline void setGameExit(bool exit) { mShouldExit = exit; };
	inline void setUnitVisionRadius(int radius) { mUnitVisionRadius = radius; };
	inline int getUnitVisionRadius() const { return mUnitVisionRadius; };
	inline Menu* getMenu() const { return mpMenu; };
	inline int getSeperationWeight() const { return mSeperationWeight; };
	inline int getCohesionWeight() const { return mCohesionWeight; };
	inline int getAlignmentWeight() const { return mAlignmentWeight; };
	inline void setSeperationWeight(const int weight) { mSeperationWeight = weight; };
	inline void setCohesionWeight(const int weight) { mCohesionWeight = weight; };
	inline void setAlignmentWeight(const int weight) { mAlignmentWeight = weight; };

private:
	GraphicsSystem* mpGraphicsSystem;
	GraphicsBufferManager* mpGraphicsBufferManager;
	SpriteManager* mpSpriteManager;
	GameMessageManager* mpMessageManager;
	UnitManager* mpUnitManager;
	InputManager* mpInputManager;
	WallManager* mpWallManager;
	Timer* mpLoopTimer;
	Timer* mpMasterTimer;
	Menu* mpMenu;
	bool mShouldExit;
	int mUnitVisionRadius;
	int mCohesionWeight;
	int mSeperationWeight;
	int mAlignmentWeight;

	//should be somewhere else
	ALLEGRO_SAMPLE* mpSample;
	IDType mBackgroundBufferID;
	IDType mPlayerIconBufferID;
	IDType mEnemyIconBufferID;
};

float genRandomBinomial();//range -1:1 from "Artificial Intelligence for Games", Millington and Funge
float genRandomFloat();//range 0:1 from "Artificial Intelligence for Games", Millington and Funge

extern Game* gpGame;
extern PerformanceTracker* gpPerformanceTracker;

#endif