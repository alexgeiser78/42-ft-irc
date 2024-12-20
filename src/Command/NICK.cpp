#include "../../includes/Command/Command.hpp"
#include "../../includes/Command/Messages.hpp"
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
		std::string errorMsg = ERR_NONICKNAMEGIVEN(client->getNickName());
		std::cout << errorMsg;
		send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
		return;
	}
	for (size_t i = 0; i < server->clients.size(); i++)
	{
		if (server->clients[i]->getNickName() == client->getArgs()[0]) // if the nickname is already taken
		{
		std::string errorMsg = ERR_NICKNAMEINUSE(client->getNickName(), client->getArgs()[0]);
			std::cout << errorMsg;
			send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
			return;
		}
	}
	if (validateNickname(client->getArgs()[0]) == false) // if the nickname is invalid
	{
		std::string errorMsg = ERR_ERRONEUSNICKNAME(client->getNickName(), client->getArgs()[0]);
		std::cout << errorMsg;
		send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
		return;
	}
    std::string successMsg = RPL_NICK(client->getNickName(), client->getArgs()[0]);
	std::cout << successMsg;
	client->setNickName(client->getArgs()[0]);// reset the NickName
    send(client->getSocket(), successMsg.c_str(), successMsg.size(), 0);
	return;
}