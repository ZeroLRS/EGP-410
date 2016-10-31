#ifndef _GAMEMESSAGE_H
#define _GAMEMESSAGE_H

#include "Trackable.h"

enum MessageType
{
	INVALID_MESSAGE_TYPE = -1,
	PLAYER_MOVETO_MESSAGE = 0,
	EXIT_GAME_MESSAGE = 1,
	SPAWN_UNIT_MESSAGE = 2,
	DELETE_UNIT_MESSAGE = 3,
	CHANGE_MENU_SELECTION_MESSAGE = 4,
	MODIFY_MENU_SELECTION_MESSAGE = 5,
	SET_MENU_SELECTION_MESSAGE = 6,
	SAVE_DATA_MESSAGE = 7,
	LOAD_DATA_MESSAGE = 8
};

class GameMessage: public Trackable
{
public:
	friend class GameMessageManager;

	GameMessage( MessageType type  );
	~GameMessage();

	double getSubmittedTime() const { return mSubmittedTime; };
	double getScheduledTime() const { return mScheduledTime; };

protected:
	MessageType mType;
	double mSubmittedTime;
	double mScheduledTime;

private:
	virtual void process() = 0; 
};

#endif