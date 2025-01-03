#include "../../includes/Network/Client.hpp"


Client::Client(void): _socket(-1), _isRegistered(false)
{
	std::cout << " Default Client object created" <<std::endl;
}

Client::Client(int sock): _socket(sock), _isRegistered(false)
{
	std::cout << "Client object created" << std::endl;
}

Client::~Client()
{
	std::cout << "Client object destroyed" << std::endl;
}

Client & Client::operator=(Client const & src)
{
	if (this != &src)
	{
		_socket = src._socket;
		_address = src._address;
		_args = src._args;
		_nickname = src._nickname;
		_username = src._username;
		_hostname = src._hostname;
		_servername = src._servername;
		_realname = src._realname;
		_isRegistered = src._isRegistered;
	}
	return *this;
}

int Client::getSocket() const
{
	return(_socket);
}

std::string Client::getNickName() const
{
	return(_nickname);
}

void	Client::setSocket(int fd)
{
	_socket = fd;
}

std::string	Client::getAddress(void) const
{
	return (_address);
}

void	Client::setAddress(std::string address)
{
	_address = address;
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

std::string	Client::getLastArg() const
{
	return _lastArg;
}

void	Client::setLastArg(const std::string &arguments)
{
    size_t  start = arguments.find(':');
    if (start == std::string::npos)
        _lastArg = "";
    else
        _lastArg = arguments.substr(start + 1);
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

void        Client::setServerCreationTime(std::string time)
{
    _ServerCreationTime = time;
}

std::string Client::getServerCreationTime(void) const
{
    return _ServerCreationTime;
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

// void Client::closeClient()
// {
//     if (_socket >= 0) 
// 	{
//         std::cout << "Closing client socket: " << _socket << std::endl;
//         close(_socket); // Close the socket using the system call
//         _socket = -1; // Set the socket to an invalid value after closing
//     }
// 	else 
//         std::cerr << "Socket already closed or invalid." << std::endl;
// }



