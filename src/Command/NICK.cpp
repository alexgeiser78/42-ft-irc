#include "../../includes/Command/Command.hpp"
#include "../../includes/Network/Client.hpp"

//NICK <nickname>

void handleNick(Client *client) 
{ 
    std::cout << "Handling NICK\n";
	std::cout << "Client Nickname: " << client->getNickName() << "\n";
	std::cout << "Client Args: " << client->getArgs()[0] << "\n";
	if (client->getArgs().size() != 1) // Nick receives only one arg 
	{
		std::string errorMsg = "ERROR: Invalid NICK command usage.\n";
		std::cout << errorMsg << std::endl;
		send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
		return;
	}
	if (client->getNickName() == client->getArgs()[0]) // if the nickname is the same as the one given
	{
		std::string errorMsg = "ERROR: Nickname is already set to " + client->getNickName() + "\n";
		std::cout << errorMsg << std::endl;
		send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
		return;
	}
	client->setNickName(client->getArgs()[0]);// reset the NickName
    std::string successMsg = "NICK changed to " + client->getNickName() + "\n";
    send(client->getSocket(), successMsg.c_str(), successMsg.size(), 0);
    std::cout << "Nickname set to: " << client->getNickName() << "\n";
}