#include "../../includes/Command/Command.hpp"

void handlePrivMsg(Client *client)  
{ 
    (void)client;
    std::cout << "Handling PrivMsg\n"; 
}

/*
void handlePrivMsg(Client* client, const std::vector<std::string>& args)
{
    if (args.size() < 2) // Require target and message
    {
        std::string errorMsg = "ERROR: PRIVMSG requires a target and message.\n";
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        return;
    }

    std::string target = args[0];  // Target (channel or user)
    std::string message = args[1]; // Message

    if (target[0] == '#') // Target is a channel
    {
        Channel* channel = client->getCurrentChannel();
        if (!channel || channel->getName() != target)
        {
            std::string errorMsg = "ERROR: No channel joined or invalid target.\n";
            send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
            return;
        }

        channel->broadcast(*client, client->getNickName() + ": " + message + "\n");
    }
    else
    {
        // Handle private message to a specific user (not shown here)
    }
}
*/
