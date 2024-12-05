#include "../../includes/Network/Client.hpp"

Client::Client(int sock): _socket(sock)
{
	std::cout << "Client object created" <<std::endl;
}


