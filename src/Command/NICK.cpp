#include "../../includes/Command/Command.hpp"
#include "../../includes/Network/Client.hpp"

void handleNick(Client &client) 
{ 
    std::cout << "Handling NICK\n"; 
	if (client.args.size() != 1)
	{
		std::string errorMsg = "ERROR: Invalid NICK command usage.\n";
		std::cout << errorMsg << std::endl;
		send(client.getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
		return;
	}

	client.setNickName(client.args[0]);// reset the NickName
    std::string successMsg = "NICK changed to " + client.getNickName() + "\n";
    send(client.getSocket(), successMsg.c_str(), successMsg.size(), 0);
    std::cout << "Nickname set to: " << client.getNickName() << "\n";
}