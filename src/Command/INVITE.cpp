#include "../../includes/Command/Command.hpp"
#include "../../includes/Command/Messages.hpp"
#include "../../includes/Network/Server.hpp"

void handleInvite(Client *client, Server * server) 
{
    std::cout << "Handling INVITE\n";
    std::vector<std::string> args = client->getArgs();
    if (args.empty()) 
    {
        std::string errorMsg = PREFIX_SERVER + ERR_NEEDMOREPARAMS_P(client->getNickName(), "INVITE");
        std::cout << errorMsg;
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
        return;
    }
    std::string channelName = args.back();

    Channel *channel = server->findChannel(channelName);
    if (channel == NULL) 
    {
        std::string errorMsg = PREFIX_SERVER + ERR_NOSUCHCHANNEL(client->getNickName(), channelName);
        std::cout << errorMsg;
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
        return;
    }

    // Check if the member is in the channel
    if (!channel->isMember(client)) {
        std::string errorMsg = PREFIX_SERVER + ERR_NOTONCHANNEL(client->getNickName(), channelName);
        std::cout << errorMsg;
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
        return;
    }

    // check if he is an operator
    if (!channel->isOperator(client)) 
    {
        std::string errorMsg = PREFIX_SERVER + ERR_CHANOPRIVSNEEDED(client->getNickName(), channelName);
        std::cout << errorMsg;
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
        return;
    }

    //
    for (size_t i = 0; i < args.size() - 1; ++i) 
    {
        std::string targetNick = args[i];
        Client *invitee = NULL;

        //search of the client with the nickname
        for (std::map<int, Client>::iterator itClient = server->getClients().begin(); itClient != server->getClients().end(); ++itClient) {
            if (itClient->second.getNickName() == targetNick) 
            {
                invitee = &(itClient->second);
                break;
            }
        }

        // If the client isn't found
        if (invitee == NULL) 
        {
            std::string errorMsg = PREFIX_SERVER + ERR_NOSUCHNICK_P(client->getNickName(), channelName, targetNick);
            std::cout << errorMsg;
            send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
            continue;
        }

        // if the client is already member of the channel
        if (channel->isMember(invitee)) 
        {
            std::string errorMsg = PREFIX_SERVER + ERR_USERONCHANNEL(client->getNickName(), invitee->getNickName(), channelName);
            std::cout << errorMsg;
            send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
            continue;
        }

        // add the client to the channel list
        channel->addInvited(invitee);

        // Send confirmation message
        std::string rplMsg = PREFIX_SERVER + RPL_INVITING(client->getNickName(), invitee->getNickName(), channelName);
        send(client->getSocket(), rplMsg.c_str(), rplMsg.size(), MSG_NOSIGNAL);

        std::string rpl2Msg = RPL_INVITED(invitee->getNickName(), client->getNickName(), channelName);
        send(invitee->getSocket(), rpl2Msg.c_str(), rpl2Msg.size(), MSG_NOSIGNAL);
    }
}