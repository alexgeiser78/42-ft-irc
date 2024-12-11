#include "../../includes/Network/Client.hpp"

Client::Client(int sock): _socket(sock), _isRegistered(false)
{
	std::cout << "Client object created" << std::endl;
}

Client::~Client()
{
	std::cout << "Client object destroyed" << std::endl;
}

int Client::getSocket() const
{
	return(_socket);
}

//-------------------------Nickname

std::string Client::getNickName() const
{
	return(_nickname);
}

void Client::setNickName(const std::string &newNick)
{
	_nickname = newNick;
}

//---------------------------Args

std::vector<std::string> Client::getArgs() const
{
	return _args;
}

void Client::setArgs(const std::vector<std::string> &arguments)
{
	_args = arguments;
}

//---------------------------Username

void Client::setUsername(std::string const &username)
{
	_username = username;
}

std::string const &Client::getUsername() const
{
	return _username;
}

//-------------------------Hostname

void Client::setHostname(std::string const &hostname) 
{ 
	_hostname = hostname; 
}

std::string const &Client::getHostname() const 
{
	return _hostname;
}

//-------------------------Servername

void Client::setServername(std::string const  &servername)
{
	_servername = servername;
}

std::string const &Client::getServername() const
{
	return _servername;
}

//-------------------------Realname

void Client::setRealname(std::string const &realname) 
{
	_realname = realname;
}

std::string  const &Client::getRealname() const 
{
	return _realname;
}

//------------------------------Register

void Client::setRegistered(bool isRegistered)
{ 
	_isRegistered = isRegistered;
}

bool Client::isRegistered() const 
{
	return _isRegistered;
}

//--------------------------Close

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


