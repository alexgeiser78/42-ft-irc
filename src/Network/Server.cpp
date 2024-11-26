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
    struct sockaddr_in addressIPv4;
    addressIPv4.sin_family = AF_INET;
    addressIPv4.sin_port = htons(this->_Port); //htons converts the unsigned short integer hostshort from host byte order to network byte order
    addressIPv4.sin_addr.s_addr = INADDR_ANY; //INADDR_ANY allows the server to accept a client connection on any interface
    
    struct pollfd NewPoll; //pollfd structure is used to describe a set of file descriptors to be monitored by the poll() function
                           //poll() function waits for one of a set of file descriptors to become ready to perform I/O
    
    SerSocketFd = socket(AF_INET, SOCK_STREAM, 0); //create a socket, AF_INET is the address family for IPv4, SOCK_STREAM is the type of socket, 0 is the protocol (default protocol related to the chosen type of socket)
    if (SerSocketFd == -1)
    {
        throw std::runtime_error("Failed to create a socket");
    }
}

void Server::CloseFDs()
{
    close(SerSocketFd);
    std::cout << "Server socket closed" << std::endl;
}

