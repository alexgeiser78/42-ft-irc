#include "../../includes/Command/Command.hpp"
#include "../../includes/Network/Client.hpp"
#include "../../includes/Network/Server.hpp"

//NICK <nickname>

static	bool validateNickname(const std::string &nickname)
{
	if (isdigit(nickname[0]))
		return false;
	for (size_t i = 0; i < nickname.size(); i++)
	{
		if (std::isspace(nickname[i]) || nickname[i] == '#' || nickname[i] == ':' || nickname[i] == '&')
			return false;
	}
	return true;
}

void handleNick(Client *client, Server * server) 
{ 
    std::cout << "Handling NICK\n";
	std::cout << "Client Nickname: " << client->getNickName() << "\n";
	std::cout << "Client Args: " << client->getArgs()[0] << "\n";
	if (client->getArgs().size() != 1 || client->getArgs()[0].empty()) // Nick receives only one arg 
	{
		std::string errorMsg = client->getNickName() + " :No nickname given\n";
		std::cout << errorMsg << std::endl;
		send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
		return;
	}
	
	for (size_t i = 0; i < server->clients.size(); i++)
	{
		if (server->clients[i].getNickName() == client->getArgs()[0]) // if the nickname is already taken
		{
			std::string errorMsg = "ERROR: Nickname is already taken\n";
			std::cout << errorMsg << std::endl;
			send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
			return;
		}
	}
	if (validateNickname(client->getArgs()[0]) == false) // if the nickname is invalid
	{
		std::string errorMsg = "<client> <nick> :Erroneus nickname\n";
		std::cout << errorMsg << std::endl;
		send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
		return;
	}
	if (client->getNickName() == client->getArgs()[0]) // if the nickname is the same as the one given
	{
		std::string errorMsg = client->getNickName() + " " + client->getArgs()[0] + " :Nickname is already in use\n";
		std::cout << errorMsg << std::endl;
		send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
		return;
	}
	client->setNickName(client->getArgs()[0]);// reset the NickName
    std::string successMsg = "NICK changed to " + client->getNickName() + "\n";
    send(client->getSocket(), successMsg.c_str(), successMsg.size(), 0);
    std::cout << "Nickname set to: " << client->getNickName() << "\n";
	if (!client->isRegistered() && !client->getUsername().empty() && !client->getHostname().empty() && !client->getServername().empty() && !client->getRealname().empty())
	{
		client->setRegistered(true);
		std::string successMsg = client->getNickName() + " has successfully registered.\n";
		std::cout << successMsg << std::endl;
		send(client->getSocket(), successMsg.c_str(), successMsg.size(), 0);
	}
	return;
}