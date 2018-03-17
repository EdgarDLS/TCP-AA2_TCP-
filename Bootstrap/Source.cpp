#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <thread>
#include <mutex>

struct direction
{
	std::string ip;
	unsigned short port;
};

std::vector<direction> aPeers;

int main()
{
	sf::TcpListener listener;
	listener.listen(50000);

	for (int i = 0; i < 4; i++)
	{
		sf::Packet packet;

		sf::TcpSocket peerSocket;
		listener.accept(peerSocket);
		
		// A falta de constructor
		// direction d(sock.getRemoteAddress(), sock.getRemotePort());

		direction d;
		d.ip = peerSocket.getRemoteAddress().toString();
		d.port = peerSocket.getRemotePort();

		// Si no se castea a integer petara en la parte del cliente
		packet << (int)aPeers.size();
		std::cout << "Numero de peers conectados: " << (int)aPeers.size() << std::endl;

		// construir 1 mensaje
		
		for (int j = 0; j < aPeers.size(); j++)
		{
			packet << aPeers[j].ip << aPeers[j].port;
		}

		peerSocket.send(packet);
		peerSocket.disconnect();
		aPeers.push_back(d);
	}
}
