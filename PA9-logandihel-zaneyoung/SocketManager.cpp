#include "SocketManager.h"

SocketManager::~SocketManager() {
	close();
}

// private functions

// will be called from constructor to establish connection
bool SocketManager::handshake() {
	bool returnStatus = false;
	sf::Socket::Status status = connect(sf::IpAddress("loveisblind.fun"), 3000);

	if (status != sf::Socket::Done)
	{
		// error...
#ifdef DEBUG
		std::cout << "Error: could not connect to server" << std::endl;
#endif
		returnStatus = false;
	}
	else {
		returnStatus = true;
#ifdef DEBUG
		std::cout << "connection successful!" << std::endl;
		std::cout << "webserver address: " << getRemoteAddress() << std::endl;
		std::cout << "webserver port: " << getRemotePort() << std::endl;
#endif
		// send message
		std::string message = "connection_request";
		send(message.c_str(), message.size()); // dont send the \0

		// await response
		char buffer[1024];
		std::size_t received = 0;
		receive(buffer, sizeof(buffer), received);
		std::cout << "The server said: " << buffer << std::endl;

	}
	
	return returnStatus;
}

float SocketManager::getHighscore() {
	std::string message = "bestscore_query";
	send(message.c_str(), message.size()); // dont send the \0

										   // await response
	char buffer[1024];
	std::size_t received = 0;
	receive(buffer, sizeof(buffer), received);
	std::cout << "The server said: " << buffer << std::endl;

	return std::atoi(buffer);
}

void SocketManager::sendHighscore(float hs) {
	char buffer[30];
	snprintf(buffer, 30, "newscore%3.3f", hs);
	send(buffer, 30); // dont send the \0
}
/*
sf::TcpSocket socket;
sf::Socket::Status status = socket.connect(sf::IpAddress("loveisblind.fun"), 3000);

if (status != sf::Socket::Done)
{
// error...
std::cout << "Error: could not connect to server" << std::endl;
return EXIT_FAILURE;
}
else {
std::cout << "connection successful!" << std::endl;
std::cout << "webserver address: " << socket.getRemoteAddress() << std::endl;
std::cout << "webserver port: " << socket.getRemotePort() << std::endl;
}

// Send a message to the connected host
sf::Uint32 x = 24;
std::string s = "hello";
double d = 5.89;
// Group the variables to send into a packet
sf::Packet packet;
packet << x << s << d;
socket.send(packet);
// Receive an answer from the server
char buffer[1024];
std::size_t received = 0;
socket.receive(buffer, sizeof(buffer), received);
std::cout << "The server said: " << buffer << std::endl;
*/