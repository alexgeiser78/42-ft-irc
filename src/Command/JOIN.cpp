#include "../../includes/Command/Command.hpp"
#include "../../includes/Command/Messages.hpp"
#include "../../includes/Network/Server.hpp"
#include <iomanip>   // Para std::setw y std::setfill
#include <errno.h>  // Para errno y strerror


//JOIN #channel or JOIN #channel1, #channel2 or JOIN #channel passsword


#include <vector>


static  void  splitParams(Client *client, std::map<std::string, std::string> &params)
{
    if (client->getArgs()[0].empty())
    {
		std::string errorMsg = "JOIN :Not enough parameters\r\n";
		//std::cout << errorMsg;
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
    std::cout << "*****Joining channel\n";
    if (channel->isMember(client))
    {
        std::cout << "Entro en el condicional isMemeber\n";
        std::string errorMsg = "JOIN :Already in channel\r\n";
        //std::cout << errorMsg;
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        return;
    }
    if (channel->getInviteOnlyMode())
    {
        std::cout << "Entro en el condicional isInviteOnlyMode\n";
        if (channel->isInvited(client) == false)
        {
            std::string errorMsg = ERR_INVITEONLYCHAN(channel->getName());
            send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
            return;
        }
    }
    std::cout << "Llego aqui 1\n";
    channel->getMembers().insert(client);
    std::cout << "Llego aqui 2\n";
    std::string successMsg = RPL_JOINMSG(client->getNickName(), client->getUsername(),
    client->getHostname(), channel->getName());
    std::cout << "Llego aqui 3\n";
    std::cout << successMsg;
    send(client->getSocket(), successMsg.c_str(), successMsg.size(), 0);
    std::string topicMsg;
    if (channel->getTopic().empty())
        topicMsg = PREFIX_SERVER + RPL_NOTOPIC(client->getNickName(), channel->getName());
    else
        topicMsg = PREFIX_SERVER + RPL_TOPIC(client->getNickName(), channel->getName(), channel->getTopic());
    std::cout << "Llego aqui 4\n";
    send(client->getSocket(), topicMsg.c_str(), topicMsg.size(), 0);
    std::string names = channel->stringMembers();
    std::string namesMsg = PREFIX_SERVER +  RPL_NAMREPLY(channel->getName(), client->getNickName(), names);
    send(client->getSocket(), namesMsg.c_str(), namesMsg.size(), 0);
    std::cout << "Llego aqui 5\n";
    channel->broadcast(client, namesMsg);
    std::cout << "Llego aqui 6\n";
    return;
}

void    joinNewChannel(Client *client, Channel *channel)
{
    //std::cout << "*****Joining new channel\n";
    //std::cout << "Channel pointer: " << channel << std::endl;
    channel->getMembers().insert(client);
    channel->addOperator(client);
    std::string successMsg = RPL_JOINMSG(client->getNickName(), client->getUsername(),
    client->getHostname(), channel->getName());
    //std::cout << successMsg;
    send(client->getSocket(), successMsg.c_str(), successMsg.size(), 0);
    std::string topicMsg;
    topicMsg = PREFIX_SERVER + RPL_NOTOPIC(client->getNickName(), channel->getName());
    //std::cout << topicMsg;
    send(client->getSocket(), topicMsg.c_str(), topicMsg.size(), 0);
    std::string names = channel->stringMembers();
    //std::cout << "Members in the channel: " <<names << std::endl;
    std::string namesMsg = PREFIX_SERVER +  RPL_NAMREPLY(channel->getName(), client->getNickName(), names);
    //std::cout << namesMsg;
    send(client->getSocket(), namesMsg.c_str(), namesMsg.size(), 0);
    return ;
}

void handleJoin(Client *client, Server *server)
{
    //std::cout << "*****Handling JOIN command\n";
    std::cout << server << std::endl;
    std::map<std::string, std::string> params;
    splitParams(client, params);
    std::cout << "salgo de splitParams" << std::endl;
    for (std::map<std::string, std::string>::iterator it = params.begin(); it != params.end(); it++)
    {
        Channel *channel = server->findChannel(it->first);
        if (channel == NULL || channel->getMembers().empty())
        {
            std::cout << "entro en channel == NULL" << std::endl;
            Channel *newChannel = new Channel(it->first);
            newChannel->setKey(it->second);
            server->addChannel(newChannel);
            joinNewChannel(client, newChannel);
            continue ;
        }
        else if (channel->getMembers().empty())
        {
            joinNewChannel(client, channel);
            continue ;
        }
        else
        {
            std::cout << "entro en channel != NULL" << std::endl;
            if ((channel->getKeyMode() && channel->getKey() != it->second)
            || (channel->getClientLimitMode() && channel->getMembers().size() >= channel->getClientLimit())
            || (channel->getInviteOnlyMode() && channel->isInvited(client) == false))
            {
                if (channel->getKeyMode() && channel->getKey() != it->second)
                {
                    std::string errorMsg = ERR_BADCHANNELKEY(channel->getName());
                    send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
                }
                if (channel->getClientLimitMode() && channel->getMembers().size() >= channel->getClientLimit())
                {
                    std::string errorMsg = ERR_CHANNELISFULL(channel->getName());
                    send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
                }
                if (channel->getInviteOnlyMode() && channel->isInvited(client) == false)
                {
                    std::string errorMsg = ERR_INVITEONLYCHAN(channel->getName());
                    send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
                }
                continue ;
            }
            else
            {
                joinChannel(client, channel);
            }
        }
    }
}


