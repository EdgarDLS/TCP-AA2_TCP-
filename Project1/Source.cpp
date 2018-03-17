#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <thread>
#include <mutex>

#define MAX_MENSAJES 30
std::mutex mut;


sf::Color CheckTextColor(int peerId)
{
	sf::Color newColor = sf::Color(0, 160, 0);

	switch (peerId)
	{
		// Blue
	case 0:
		newColor = sf::Color(0, 206, 209);
		break;
		// Green
	case 1:
		newColor = sf::Color(0, 160, 0);
		break;
		// Yellow
	case 2:
		newColor = sf::Color(230, 230, 0);
		break;
		// Orange
	case 3:
		newColor = sf::Color(255, 180, 0);
		break;
		// White
	case 4:
		newColor = sf::Color(255, 255, 255);
		break;
	}

	return newColor;
}

void thread_socket_selector(std::vector<std::string>* aMsjs, std::vector<int>* msgColor, std::vector<sf::TcpSocket*> peers)
{
	sf::SocketSelector socketSelector;
	sf::Packet packet;
	sf::Socket::Status status;
	sf::String text;

	int peerId;

	for (int i = 0; i < peers.size(); i++)
		socketSelector.add(*peers[i]);


	while (socketSelector.wait())
	{
		for (int i = 0; i < peers.size(); i++)
		{
			if (socketSelector.isReady(*peers[i]))
			{
				status = peers[i]->receive(packet);
				packet >> text >> peerId;

				if (status == sf::Socket::Status::Disconnected)
				{
					socketSelector.remove(*peers[i]);
					peers[i]->disconnect();
					peers.erase(peers.begin() + i);

					aMsjs->push_back("Se ha desconectado un jugador");
					msgColor->push_back(4);
				}
				else
				{
					aMsjs->push_back(text);
					msgColor->push_back(peerId);

					while (aMsjs->size() > 25)
						aMsjs->erase(aMsjs->begin() + i);
				}
				break;
			}
		}
	}
}

int main()
{
	std::vector<std::string> aMensajes;
	std::vector<int> messageColor;

	sf::TcpSocket socket;
	std::vector<sf::TcpSocket*> peersVector;
	sf::TcpListener listener;
	sf::Packet packet;

	std::string ip;
	unsigned short port;
	int peers;

	sf::Socket::Status status = socket.connect("localhost", 50000, sf::milliseconds(15.f));

	if (status != sf::Socket::Done)
	{
		std::cout << "Error al establecer conexion\n";
		exit(0);
	}
	else
	{
		std::cout << "Se ha establecido conexion\n";
		socket.receive(packet);

		// Client number
		packet >> peers;
		std::cout << "Peers actuales: " << peers << std::endl;

		for (int i = 0; i < peers; i++)
		{
			// IP and Port
			packet >> ip >> port;


			sf::TcpSocket* aux = new sf::TcpSocket();
			status = aux->connect(ip, port);

			if (status != sf::Socket::Done)
			{
				std::cout << "Error al establecer conexion\n";
				exit(0);
			}
			else
			{
				std::cout << "Conectado con >> IP: " << ip << " | PORT: " << port << std::endl;
				peersVector.push_back(aux);
			}
		}

		int newPort = socket.getLocalPort();

		// We don´t need the socket anymore;
		socket.disconnect();

		listener.listen(newPort);

		sf::TcpListener::Status peerStatus;
		while (peersVector.size() < 3)
		{
			std::cout << "While | Vector Size: " << peersVector.size() << std::endl;
			sf::TcpSocket* peerSocket = new sf::TcpSocket;
			peerStatus = listener.accept(*peerSocket);

			// If its accepted then we put it in the peers vector.
			if (peerStatus == sf::TcpListener::Done)
			{
				peersVector.push_back(peerSocket);
			}
		}
	}

	std::cout << "Todos los clientes se han conectado" << std::endl;
	aMensajes.push_back("Todos los clientes estan listos");
	messageColor.push_back(4);
	std::cout << "Peer numero: " << peers << std::endl;

	// PARTE GRAFICA

	sf::Vector2i screenDimensions(800, 600);

	sf::RenderWindow window;
	window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Chat");

	sf::Font font;
	if (!font.loadFromFile("DroidSans.ttf"))
	{
		std::cout << "Can't load the font file" << std::endl;
	}

	sf::String mensaje = " >";

	sf::Text chattingText(mensaje, font, 14);
	chattingText.setFillColor(sf::Color(0, 160, 0));
	chattingText.setStyle(sf::Text::Bold);


	sf::Text text(mensaje, font, 14);
	text.setFillColor(CheckTextColor(peers));
	text.setStyle(sf::Text::Bold);
	text.setPosition(0, 560);

	sf::RectangleShape separator(sf::Vector2f(800, 5));
	separator.setFillColor(sf::Color(200, 200, 200, 255));
	separator.setPosition(0, 550);

	// Thread to receive packets
	std::thread sockSelecThread(&thread_socket_selector, &aMensajes, &messageColor, peersVector);

	while (window.isOpen())
	{
		sf::Event evento;
		while (window.pollEvent(evento))
		{
			switch (evento.type)
			{
			case sf::Event::Closed:
				window.close();
				exit(0);
				break;
			case sf::Event::KeyPressed:
				if (evento.key.code == sf::Keyboard::Escape)
					window.close();
				else if (evento.key.code == sf::Keyboard::Return)
				{
					sf::Packet packet;
					packet << mensaje << peers;

					aMensajes.push_back(mensaje);
					messageColor.push_back(peers);

					// Send the message to the rest of the clients.
					for (int i = 0; i < peersVector.size(); i++)
						peersVector[i]->send(packet);

					if (aMensajes.size() > 25)
					{
						mut.lock();
						aMensajes.erase(aMensajes.begin(), aMensajes.begin() + 1);
						mut.unlock();
					}

					mensaje = ">";
				}
				break;
			case sf::Event::TextEntered:
				if (evento.text.unicode >= 32 && evento.text.unicode <= 126)
					mensaje += (char)evento.text.unicode;
				else if (evento.text.unicode == 8 && mensaje.getSize() > 0)
					mensaje.erase(mensaje.getSize() - 1, mensaje.getSize());
				break;
			}
		}

		window.draw(separator);
		for (size_t i = 0; i < aMensajes.size(); i++)
		{
			std::string chatting = aMensajes[i];
			chattingText.setFillColor(CheckTextColor(messageColor[i]));
			chattingText.setPosition(sf::Vector2f(0, 20 * i));
			chattingText.setString(chatting);
			window.draw(chattingText);
		}
		std::string mensaje_ = mensaje + "_";
		text.setString(mensaje_);
		window.draw(text);


		window.display();
		window.clear();
	}

	sockSelecThread.join();
}