#include "../../includes/Command/Command.hpp"
#include "../../includes/Network/Channel.hpp"
#include "../../includes/Network/Client.hpp"

//JOIN #channel or JOIN #channel1, #channel2 or JOIN #channel passsword

void handleJoin(Client &client)  
{ 
    std::cout << "Handling JOIN\n";
    const std::vector<std::string> &args = client.getArgs(); //catch the args provided by the client in a vector called &args

    if (args.empty()) //if no args, error msg to client and server
    {
        std::string errorMsg = "ERROR: JOIN command requires a channel name\n";
        send(client.getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        std::cerr << "Client " << client.getSocket() << ": JOIN command missing channel name\n";
        return;
    }

    std::vector<std::string> channelNames; //vector of args
    std::stringstream ss(args[0]); // takes the first args, meaning the channels
    std::string channelName; //string of separated channnel

    //multiple channels args cut
    while (std::getline(ss, channelName, ',')) // cut the ss at the "," and put it in channelName 
    {
        if (!channelName.empty())
        {
            channelNames.push_back(channelName);
        }
    }
    
    for (size_t i = 0; i < channelName.size(); ++i) //for every channelName extracted 
    {
        std::string const &channelName = channelNames[i]; //access to the channel name from channelNames[i]

        if (channelName[0] != '#') // "#" check 
        {
            std::string errorMsg = "ERROR: Channel name must start with '#'. Invalid channel: " + channelName + "\n";
            send(client.getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
            std::cerr << "Client " << client.getSocket() << ": Invalid channel name " << channelName << "\n";
            continue;
        }

        Channel* channel = Channel::getOrCreateChannel(channelName); //if the channnel already exist, it returns a pointer to it or it creates it
        
        if (channel == NULL)
        {
            std::string errorMsg = "ERROR: Unable to join channel " + channelName + ".\n";
            send(client.getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
            continue;
        }

        if (channel->addMember(client)) //if the client isn't member of the channel, it is added 
        {
            std::string successMsg = "Joined " + channelName + "\n";
            send(client.getSocket(), successMsg.c_str(), successMsg.size(), 0);
            std::cout << "Client " << client.getSocket() << " joined channel " << channelName << "\n";

            channel->broadcast(client, "User " + client.getNickName() + " has joined the channel.\n");//send messages to the others clients
        }
        else //if the client is already member, send msg to client and server
        {
            std::string errorMsg = "ERROR: Already in channel " + channelName + "\n";
            send(client.getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        }
    }
}