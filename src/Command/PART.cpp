#include "../../includes/Command/Command.hpp"
#include "../../includes/Network/Channel.hpp"
#include "../../includes/Network/Client.hpp"

//PART #channel or PART #channel, #channel2

void handlePart(Client &client) 
{
    std::cout << "Handling PART\n";
    const std::vector<std::string> &args = client.getArgs(); //retrieves the args

    if (args.empty())
    {
        std::string errorMsg = "ERROR: PART command requires a channel name\n";
        send(client.getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        std::cerr << "Client " << client.getSocket() << ": PART command missing channel name\n";
        return;
    }

    std::vector<std::string> channelNames;
    std::stringstream ss(args[0]);
    std::string channelName;

    while (std::getline(ss, channelName, ','))
    {
        if (!channelName.empty())
        {
            channelNames.push_back(channelName);
        }
    }

    for (size_t i = 0; i < channelNames.size(); ++i) //loop through the parsed channel names
    {
        std::string const &channelName = channelNames[i];
        
        if (channelName[0] != '#') 
        {
            std::string errorMsg = "ERROR: Channel name must start with '#'. Invalid channel: " + channelName + "\n";
            send(client.getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
            std::cerr << "Client " << client.getSocket() << ": Invalid channel name " << channelName << "\n";
            continue;
        }

        Channel *channel = Channel::getChannel(channelName);
        
        if (channel == NULL)
        {
            std::string errorMsg = "ERROR: Channel " + channelName + " does not exist.\n";
            send(client.getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
            continue;
        }

        if (!channel->isMember(client))
        {
            std::string errorMsg = "ERROR: You are not in channel " + channelName + ".\n";
            send(client.getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
            continue;
        }

        channel->removeMember(client);
        std::string successMsg = "Left channel " + channelName + "\n";
        send(client.getSocket(), successMsg.c_str(), successMsg.size(), 0);
        std::cout << "Client " << client.getSocket() << " left channel " << channelName << "\n";

        channel->broadcast(client, "User " + client.getNickName() + " has left the channel.\n");
    }

}

