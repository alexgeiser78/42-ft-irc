#include "../../includes/network/Server.hpp"

Server::Server(int port): _Port(port)
{
    this->_Port = port;
    std::cout << "Server object created" << std::endl;
}

Server::~Server()
{
    close(SerSocketFd);
    std::cout << "Server object destroyed" << std::endl;
}

void Server::SignalHandler(int signum)
{
    std::cout << "Interrupt signal (" << signum << ") received.\n";
    exit(signum);
}

void Server::ServerInit(int port)
{
	this->_Port = port;
	SerSocket(); //-> create the server socket

	std::cout <<"Server " << SerSocketFd << " Connected" << std::endl;
	std::cout << "Waiting to accept a connection...\n";
}

void Server::SerSocket()
{
    // Create a socket
    SerSocketFd = socket(AF_INET, SOCK_STREAM, 0); //create a socket, AF_INET is the address family for IPv4, SOCK_STREAM is the type of socket, 0 is the protocol  
    if (SerSocketFd == -1)
    {
        throw std::runtime_error("Failed to create a socket");
    }
/*
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(this->Port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    std::cout << "Socket created" << std::endl;
    */
}

void Server::CloseFDs()
{
    close(SerSocketFd);
    std::cout << "Server socket closed" << std::endl;
}

