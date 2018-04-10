// PA9-logandihel-zaneyoung.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
#include <iostream>

int main()
{
	
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
	
	Game game("ripoff racecar");
	game.start();
    return 0;
}

