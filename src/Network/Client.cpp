#include "../../includes/Network/Client.hpp"

Client::Client(int sock): _socket(sock)
{
	std::cout << "Client object created" << std::endl;
}

Client::~Client()
{
	std::cout << "Client object destroyed" << std::endl;
}

std::string Client::getNickName() const
{
	return(_nickname);
}

int Client::getSocket() const
{
	return(_socket);
}

void Client::setNickName(const std::string &newNick)
{
	_nickname = newNick;
}

void Client::setArgs(const std::vector<std::string> &arguments)

{
	_args = arguments;
}

std::vector<std::string> Client::getArgs() const
{
	return _args;
}

void Client::closeClient()
{
    if (_socket >= 0) 
	{
        std::cout << "Closing client socket: " << _socket << std::endl;
        close(_socket); // Close the socket using the system call
        _socket = -1; // Set the socket to an invalid value after closing
    }
	else 
        std::cerr << "Socket already closed or invalid." << std::endl;
}


