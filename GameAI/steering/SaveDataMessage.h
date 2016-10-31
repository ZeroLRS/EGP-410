#ifndef _SAVEDATAMESSAGE_H
#define _SAVEDATAMESSAGE_H

#include "GameMessage.h"

class SaveDataMessage : public GameMessage
{
public:
	SaveDataMessage();
	~SaveDataMessage();

	void process();

private:
};

#endif