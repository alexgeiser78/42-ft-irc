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
    if (channel->isMember(client))
    {
        std::string errorMsg = "JOIN :Already in channel\r\n";
        //std::cout << errorMsg;
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        return;
    }
    if (channel->getInviteOnlyMode())
    {
        if (channel->isInvited(client) == false)
        {
            //std::cout << "Client not invited\n";
            std::string errorMsg = ERR_INVITEONLYCHAN(channel->getName());
            //std::cout << errorMsg;
            send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
            return;
        }
    }
    channel->getMembers().insert(client);
    std::string successMsg = RPL_JOINMSG(client->getNickName(), client->getUsername(),
    client->getHostname(), channel->getName());
    std::cout << successMsg;
    send(client->getSocket(), successMsg.c_str(), successMsg.size(), 0);
    std::string topicMsg;
    if (channel->getTopic().empty())
        topicMsg = PREFIX_SERVER + RPL_NOTOPIC(client->getNickName(), channel->getName());
    else
        topicMsg = PREFIX_SERVER + RPL_TOPIC(client->getNickName(), channel->getName(), channel->getTopic());
    //std::cout << topicMsg;
    send(client->getSocket(), topicMsg.c_str(), topicMsg.size(), 0);
    std::string names = channel->stringMembers();
    std::string namesMsg = PREFIX_SERVER +  RPL_NAMREPLY(channel->getName(), client->getNickName(), names);
    //std::cout << namesMsg;
    send(client->getSocket(), namesMsg.c_str(), namesMsg.size(), 0);
    channel->broadcast(client, namesMsg);
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
    int flag = 0;
    std::map<std::string, std::string> params;
    splitParams(client, params);
    for (std::map<std::string, std::string>::iterator it = params.begin(); it != params.end(); it++)
    {
        for (size_t i = 0; i < server->getChannels().size(); i++)
        {
            if (server->getChannels()[i]->getName() == it->first)
            {
                flag = 1;
                if ((!server->getChannels()[i]->getKeyMode() || server->getChannels()[i]->getKey() == it->second)
                && (!server->getChannels()[i]->getClientLimitMode()
                    || server->getChannels()[i]->getMembers().size() < server->getChannels()[i]->getClientLimit()))
                {
                    joinChannel(client, server->getChannels()[i]);
                    break ;
                }
                if (server->getChannels()[i]->getKeyMode() && server->getChannels()[i]->getKey() != it->second)
                {
                    std::string errorMsg = ERR_BADCHANNELKEY(server->getChannels()[i]->getName());
                    //std::cout << errorMsg;
                    send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
                }
                if (server->getChannels()[i]->getClientLimitMode()
                && server->getChannels()[i]->getMembers().size() >= server->getChannels()[i]->getClientLimit())
                {
                    std::string errorMsg = ERR_CHANNELISFULL(server->getChannels()[i]->getName());
                    //std::cout << errorMsg;
                    send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);}
                break ;
            }
        }
        if (flag == 0)
        {
            Channel *newChannel = new Channel(it->first);
            newChannel->setKey(it->second);
            server->addChannel(newChannel);
            joinNewChannel(client, newChannel);
        }
        //std::cout << "Channels size: " << server->getChannels().size() << std::endl;
    }
}


