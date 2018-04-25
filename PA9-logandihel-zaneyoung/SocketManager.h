#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include "testing.h"
#include <SFML/Network.hpp>
#include <string>
#include <iostream>
#include <exception>

using std::string;
using std::to_string;
using std::exception;
/*
SocketManager.h
Includes methods for handling the sockets
and the custom protocols we are using 
to send over TCP connections
*/

class SocketManager : public sf::TcpSocket {
public:
	SocketManager() : sf::TcpSocket() {
		if (!handshake()) {
			handshakeSuccess = false;
			//throw exception("Could not handshake with server. Online access not avaliable");
		}
		else {
			handshakeSuccess = true;
		}
	}
	~SocketManager();


	float getHighscore();
	void sendHighscore(float hs);

private:
	bool handshake();
	bool handshakeSuccess;
	int serverID; // server tells us our custom ID
};
#endif