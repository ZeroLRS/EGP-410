#ifndef _LOADDATAMESSAGE_H
#define _LOADDATAMESSAGE_H

#include "GameMessage.h"

class LoadDataMessage : public GameMessage
{
public:
	LoadDataMessage();
	~LoadDataMessage();

	void process();

private:
};

#endif