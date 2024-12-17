#include "../../includes/Command/Command.hpp"
#include "../../includes/Command/Messages.hpp"
#include "../../includes/Network/Channel.hpp"
#include "../../includes/Network/Client.hpp"
#include "../../includes/Network/Server.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>   // Para std::setw y std::setfill
#include <unistd.h>  // Para el envío de sockets y error handling
#include <cstring>
#include <errno.h>  // Para errno y strerror


//JOIN #channel or JOIN #channel1, #channel2 or JOIN #channel passsword


#include <vector>


static  void  splitParams(Client *client, std::map<std::string, std::string> &params)
{
    // std::map<std::string, std::string> params;
    if (client->getArgs()[0].empty())
    {
		std::string errorMsg = "JOIN :Not enough parameters\r\n";
		std::cout << errorMsg;
		send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
		return;         
    }
    std::stringstream streamChannels(client->getArgs()[0]);
    std::string channel;
    if (client->getArgs().size() == 1)
    {
        while(std::getline(streamChannels, channel, ','))
        {
            params.insert(std::pair<std::string, std::string>(channel, ""));
        }
    }
    if (client->getArgs().size() > 1)
    {
        std::stringstream streamKeys(client->getArgs()[1]);
        std::string key;
        while(std::getline(streamChannels, channel, ','))
        {
            if (std::getline(streamKeys, key, ','))
                params.insert(std::pair<std::string, std::string>(channel, key));
            else
            params.insert(std::pair<std::string, std::string>(channel, ""));
        }
    }
    return;
}

void    joinChannel(Client *client, Channel *channel)
{
    std::cout << "Joining channel\n";
    if (channel->isMember(*client))
    {
        std::string errorMsg = "JOIN :Already in channel\r\n";
        std::cout << errorMsg;
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        return;
    }
    channel->addMember(*client);
    std::string successMsg = RPL_JOINMSG(client->getNickName(), client->getUsername(),
    client->getHostname(), channel->getName());
    std::cout << successMsg;
    send(client->getSocket(), successMsg.c_str(), successMsg.size(), 0);
    return;
}

void    joinNewChannel(Client *client, Channel *channel, std::map<std::string, std::string>::iterator it)
{
    (void)it;
    // (void)client;
    // (void)channel;

    std::cout << "Joining new channel\n";
    channel->addMember(*client);
    std::string successMsg = RPL_JOINMSG(client->getNickName(), client->getUsername(),
    client->getHostname(), channel->getName());
    std::cout << successMsg;
    send(client->getSocket(), successMsg.c_str(), successMsg.size(), 0);
    return ;
}

void handleJoin(Client *client, Server *server)
{
    std::map<std::string, std::string> params;
    splitParams(client, params);
    for (std::map<std::string, std::string>::iterator it = params.begin(); it != params.end(); it++)
    {
        std::cout << "Channel: " << it->first << " Key: " << it->second << std::endl;
        for (size_t i = 0; i < server->channels.size(); i++)
        {
            if (server->channels[i].getName() == it->first)
            {
                if ((server->channels[i].getKey().empty() || server->channels[i].getKey() == it->second)
                && (!server->channels[i].getClientLimitMode()
                    || server->channels[i].getMembers().size() < server->channels[i].getClientLimit()))
                {
                    joinChannel(client, &server->channels[i]);
                    return ;
                }
                if (server->channels[i].getKey() != it->second)
                {
                    std::string errorMsg = ERR_BADCHANNELKEY(server->channels[i].getName());
                    std::cout << errorMsg;
                    send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
                }
                if (server->channels[i].getMembers().size() >= server->channels[i].getClientLimit())
                {
                    std::string errorMsg = "JOIN :Channel is full\r\n";
                    std::cout << errorMsg;
                    send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);}
                return ;
            }
        }
        Channel *newChannel = new Channel(it->first);
        server->channels.push_back(*newChannel);
        joinNewChannel(client, newChannel, it);
    }
}


