// TimeTrialClient.hpp

#ifndef _TIMETRIALCLIENT_H_
#define _TIMETRIALCLIENT_H_

// include Windows headers
#include <windows.h>
#include <winsock.h>

// include STL headers
#include <limits>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>

// include client/server protocol headers
#include "../ClientServerProtocol/clientserverprotocol.h"

class Client {
protected:
	Client();
	virtual ~Client();
public:
	static Client &instance();
public:
	bool connectToServer(const int _port);
	bool disconnectFromServer();
public:
	bool sendMessage(const ClientServerMessage &_message);
private:
	bool m_connected;
	SOCKET m_socket;
};

#endif
