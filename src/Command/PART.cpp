#include "../../includes/Command/Command.hpp"
#include "../../includes/Network/Server.hpp"

//PART #channel or PART #channel, #channel2

void handlePart(Client *client, Server * server) //function to handle the PART command
{

    (void)server;

    std::cout << "Handling PART\n";
    const std::vector<std::string> &args = client->getArgs(); //retrieves the args

    if (args.empty())
    {
        std::string errorMsg = "ERROR: PART command requires a channel name\n";
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        std::cerr << "Client " << client->getSocket() << ": PART command missing channel name\n";
        return;
    }

    for (size_t i = 0; i < args.size(); ++i) //multiple args
    {
        std::string const &channelName = args[i];

        Channel *channel = NULL;
        channel = server->findChannel(channelName); //find the channel
        if (channel == NULL)
        {
            std::string errorMsg = "ERROR: Channel " + channelName + " does not exist.\n";
            send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
            continue;
        }

        if (!channel->isMember(client))
        {
            std::string errorMsg = "ERROR: You are not in channel " + channelName + ".\n";
            send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
            continue;
        }

        channel->removeMember(client);
        std::string successMsg = "Left channel " + channelName + "\n";
        send(client->getSocket(), successMsg.c_str(), successMsg.size(), 0);
        std::cout << "Client " << client->getSocket() << " left channel " << channelName << "\n";

        channel->broadcast(client, "User " + client->getNickName() + " has left the channel.\n");
    }

}

