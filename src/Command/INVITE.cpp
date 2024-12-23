#include "../../includes/Command/Command.hpp"
#include "../../includes/Command/Messages.hpp"
#include "../../includes/Network/Channel.hpp"
#include "../../includes/Network/Client.hpp"
#include "../../includes/Network/Server.hpp"

static  Channel *getChannel(Server *server, Client *client, std::string args)
{
    std::cout << "Entro en getChannel" << std::endl;
    Channel *channel = NULL;
    std::cout << "Llego aqui" << std::endl;
    if (server->channels.size() == 0)
    {
        return (NULL);
    }
    for (std::vector<Channel *>::iterator it = server->channels.begin(); it != server->channels.end(); it++)
    {
        if ((*it)->getName() == args)
            channel = *it;
    }
    if (channel == NULL)
    {
        std::string errorMsg = PREFIX_SERVER + ERR_NOSUCHCHANNEL(client->getNickName(), channel->getName());
        std::cout << errorMsg;
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
    }
    return (channel);
}

void handleInvite(Client *client, Server * server) 
{
    std::cout << "Handling INVITE\n";
    std::vector<std::string> args = client->getArgs();
    if (args.size() == 0)
        return ;
    Channel *channel = NULL;
    channel = getChannel(server, client, args[args.size() - 1]);
    if (channel == NULL)
    {
        std::string errorMsg = PREFIX_SERVER + ERR_NOTONCHANNEL(client->getNickName(), args[args.size() - 1]);
        std::cout << errorMsg;
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
        return;
    }
    if (!channel->isMember(client))
    {
        std::string errorMsg = PREFIX_SERVER + ERR_NOTONCHANNEL(client->getNickName(), args[args.size() - 1]);
        std::cout << errorMsg;
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
        return;
    }
    if (!channel->isOperator(client))
    {
        std::string errorMsg = PREFIX_SERVER + ERR_CHANOPRIVSNEEDED(client->getNickName(), channel->getName());
        std::cout << errorMsg;
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
        return;
    }
    if (args.size() == 1)
    {
        std::string errorMsg = PREFIX_SERVER + ERR_NEEDMOREPARAMS(client->getNickName(), "INVITE");
        std::cout << errorMsg;
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
        return;
    }
    std::cout <<"Llego aqui" << std::endl;
    for (std::vector<std::string>::iterator it = args.begin(); it != args.end() - 1; it++)
    {
        std::cout << "Entra a invitar" << std::endl;
        Client *invitee = NULL;
        for (std::vector<Client *>::iterator itClient = server->clients.begin(); itClient != server->clients.end(); itClient++)
        {
            std::cout << "Entra a detectar el nick" << std::endl;
            if ((*itClient)->getNickName() == *it)
                invitee = *itClient;
        }
        if (invitee == NULL)
        {
            std::cout << "Entra a n ha encontrado el nick" << std::endl;
            std::string errorMsg = PREFIX_SERVER + ERR_NOSUCHNICK(client->getNickName(), channel->getName(), *it);
            std::cout << errorMsg;
            send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
            continue;
        }
        if (channel->isMember(invitee))
        {
            std::cout << "Entra a mirar si el nick ya esta en el canal" << std::endl;
            std::string errorMsg = PREFIX_SERVER + ERR_USERONCHANNEL(client->getNickName(), invitee->getNickName(), channel->getName());
            std::cout << errorMsg;
            send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
            continue;
        }
        channel->addInvited(invitee);
        std::cout << "Invita" << std::endl;
        std::string rplMsg = PREFIX_SERVER + RPL_INVITING(client->getNickName(), invitee->getNickName(), channel->getName());
        std::cout << rplMsg;
        send(client->getSocket(), rplMsg.c_str(), rplMsg.size(), MSG_NOSIGNAL);
        std::string rpl2Msg = RPL_INVITED(invitee->getNickName(), client->getNickName(), channel->getName());
        std::cout << rpl2Msg;
        send(invitee->getSocket(), rpl2Msg.c_str(), rpl2Msg.size(), MSG_NOSIGNAL);
    }
}