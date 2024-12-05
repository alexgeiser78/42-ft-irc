#include "../../includes/Command/Command.hpp"
#include "../../includes/Network/Client.hpp"

void handleNick(Client &client) 
{ 
    std::cout << "Handling NICK\n"; 
	if (client.args.size() != 1)
	{
		std::string errorMsg = "ERROR: Invalid NICK command usage.\n";
		std::cout << errorMSG << std::endl;
		send(client.socket, errorMsg.c_str(), errorMsg.size(), 0);
return;
	}

client.nickname = client.args[0];  // Mettre à jour le pseudo
    std::string successMsg = "NICK changed to " + client.nickname + "\n";
    send(client.socket, successMsg.c_str(), successMsg.size(), 0);
    std::cout << "Nickname set to: " << client.nickname << "\n";


