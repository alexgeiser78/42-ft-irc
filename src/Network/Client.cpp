#include "../../includes/Network/Client.hpp"

Client::Client(int sock): _socket(sock)
{
	std::cout << "Client object created" <<std::endl;
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

