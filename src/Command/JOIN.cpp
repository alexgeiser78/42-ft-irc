#include "../../includes/Command/Command.hpp"
#include "../../includes/Network/Channel.hpp"
#include "../../includes/Network/Client.hpp"

void handleJoin(Client &client)  
{ 
    std::cout << "Handling JOIN\n";
    const std::vector<std::string> &args = client.getArgs();

    if (args.empty())
    {
        std::string errorMsg = "ERROR: JOIN command requires a channel name\n";
        send(client.getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        std::cerr << "Client " << client.getSocket() << ": JOIN command missing channel name\n";
        return;
    }

    for (size_t i = 0; i < args.size(); ++i)
    {
        const std::string& channelName = args[i]; //extract the channel name from args[i]

        Channel* channel = Channel::getOrCreateChannel(channelName);
    
        if (channel == NULL)
        {
            std::string errorMsg = "ERROR: Unable to join channel " + channelName + ".\n";
            send(client.getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
            continue;
        }

        if (channel->addMember(client))
        {
            std::string successMsg = "Joined " + channelName + "\n";
            send(client.getSocket(), successMsg.c_str(), successMsg.size(), 0);
            std::cout << "Client " << client.getSocket() << " joined channel " << channelName << "\n";

            channel->broadcast(client, "User " + client.getNickName() + " has joined the channel.\n");
        }
        else
        {
            std::string errorMsg = "ERROR: Already in channel " + channelName + "\n";
            send(client.getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        }
    }
}