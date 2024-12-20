#include "../../includes/Command/Command.hpp"
#include "../../includes/Command/Messages.hpp"
#include "../../includes/Network/Channel.hpp"
#include "../../includes/Network/Client.hpp"
#include "../../includes/Network/Server.hpp"
#include <string>

/*
i = channel on invitation only
t = only operators can change the channel topic
k = channel protected by a password
o = operators management
l = numbers of users limitation */

static  Channel *getChannel(Server *server, Client *client, std::string args)
{
    Channel *channel = NULL;
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

static std::string getModesString(Channel *channel, Client *client)
{
    std::string modes;
    int operation = 1;

    modes.clear();
    if (!channel->getProtectedTopicMode())
    {
        operation = 0;
        modes.push_back('-');
    }
    else
        modes.push_back('+');
    modes.push_back('t');
    if (channel->getInviteOnlyMode() && !operation)
    {
        modes.push_back('+');
        operation = 1;
    }
    else if (!channel->getInviteOnlyMode() && operation)
    {
        modes.push_back('-');
        operation = 0;
    }
    modes.push_back('i');
    if (channel->getKeyMode() && !operation)
    {
        modes.push_back('+');
        operation = 1;
    }
    else if (!channel->getKeyMode() && operation)
    {
        modes.push_back('-');
        operation = 0;
    }
    modes.push_back('k');
    if (channel->getClientLimitMode() && !operation)
    {
        modes.push_back('+');
        operation = 1;
    }
    else if (!channel->getClientLimitMode() && operation)
    {
        modes.push_back('-');
        operation = 0;
    }
    modes.push_back('l');
    if (channel->isOperator(client) && !operation)
    {
        modes.push_back('+');
    }
    else if (!channel->isOperator(client) && operation)
    {
        modes.push_back('-');
    }
    modes.push_back('o');
    if (channel->getKeyMode())
    {
        modes.push_back(' ');
        modes.append(channel->getKey());
    }
    if (channel->getClientLimitMode())
    {
        std::stringstream ss;
        ss << channel->getClientLimit();
        modes.push_back(' ');
        modes.append(ss.str());
    }
    return (modes);
}
static size_t getNeededParams(std::string mode)
{
    size_t neededParams = 0;
    for (size_t i = 0; i < mode.size(); i++)
    {
        if (mode[i] == 'o' || mode[i] == 'k' || mode[i] == 'l')
            neededParams++;
    }
    return (neededParams);
}

// void handleMode(Client *client, Server * server)  
// {
//     std::cout << "Handling MODE\n";
//     Channel *channel = NULL;
//     std::vector<std::string> args = client->getArgs();
//     if (args.size() == 0)
//     {
//         std::string errorMsg = PREFIX_SERVER + ERR_NEEDMOREPARAMS_MODE(client->getNickName());
//         std::cout << errorMsg;
//         send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
//         return;
//     }
//     channel = getChannel(server, client, args[0]);
//     if (channel == NULL)
//         return;
//     if (args.size() == 1)
//     {
//         std::string modes = getModesString(channel, client);
//         std::string rplMsg = PREFIX_SERVER + RPL_CHANNELMODEIS(client->getNickName(), channel->getName(), modes);
//         std::cout << rplMsg;
//         send(client->getSocket(), rplMsg.c_str(), rplMsg.size(), 0);
//         return;
//     }
//     size_t neededParams = getNeededParams(args[1]);
//     if (args.size() - 2 < neededParams)
//     {
//         std::string errorMsg = PREFIX_SERVER + ERR_NEEDMOREPARAMS_MODE(client->getNickName());
//         std::cout << errorMsg;
//         send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
//         return;
//     }
//     if (!channel->isOperator(client))
//     {
//         std::string errorMsg = PREFIX_SERVER + ERR_CHANOPRIVSNEEDED(client->getNickName(), channel->getName());
//         std::cout << errorMsg;
//         send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
//         return;
//     }
//     changeModes(channel, client, args);
// }

void    setOperator(Client *client, Channel *channel, std::vector<std::string>::iterator itParams, int operation)
{
    std::cout << "Setting operator, param: " << *itParams << std::endl;
    // if (operation)
    //     channel->setOperator(client);
    // else
    //     channel->setOperator(NULL);
}

void    changeModes(Channel *channel, Client *client, std::vector<std::string> args)
{
    // std::string modes = args[1];
    std::map<std::string, void(*)(Client *, Channel *, std::vector<std::string>::iterator, int)> modes;
    modes["o"] = setOperator;
    // modes["k"] = setKey;
    // modes["l"] = setClientLimit;
    // modes["t"] = setProtectedTopicMode;
    // modes["i"] = setInviteOnlyMode;
    int operation = 1;
    std::vector<std::string>::iterator itParams = args.begin() + 2;
    for (size_t i = 0; i < args[1].size(); i++)
    {
        if (args[1][i] == '+' || args[1][i] == '-')
            operation = (args[1][i] == '+') ? 1 : 0;
        else if (args[1].find(modes[i]) != args[1].end())
        {
            modes[modes[i]](client, channel, itParams, operation);
            itParams++;
        }
    }
}

// void    setOperator(Client *client, Channel *channel, std::vector<std::string>::iterator itParams, int operation)
// {
//     std::cout << "Setting operator, param: " << *itParams << std::endl;
//     // if (operation)
//     //     channel->setOperator(client);
//     // else
//     //     channel->setOperator(NULL);
// }

void handleMode(Client *client, Server * server)  
{
    std::cout << "Handling MODE\n";
    Channel *channel = NULL;
    std::vector<std::string> args = client->getArgs();
    if (args.size() == 0)
    {
        std::string errorMsg = PREFIX_SERVER + ERR_NEEDMOREPARAMS_MODE(client->getNickName());
        std::cout << errorMsg;
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        return;
    }
    channel = getChannel(server, client, args[0]);
    if (channel == NULL)
        return;
    if (args.size() == 1)
    {
        std::string modes = getModesString(channel, client);
        std::string rplMsg = PREFIX_SERVER + RPL_CHANNELMODEIS(client->getNickName(), channel->getName(), modes);
        std::cout << rplMsg;
        send(client->getSocket(), rplMsg.c_str(), rplMsg.size(), 0);
        return;
    }
    size_t neededParams = getNeededParams(args[1]);
    if (args.size() - 2 < neededParams)
    {
        std::string errorMsg = PREFIX_SERVER + ERR_NEEDMOREPARAMS_MODE(client->getNickName());
        std::cout << errorMsg;
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        return;
    }
    if (!channel->isOperator(client))
    {
        std::string errorMsg = PREFIX_SERVER + ERR_CHANOPRIVSNEEDED(client->getNickName(), channel->getName());
        std::cout << errorMsg;
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        return;
    }
    changeModes(channel, client, args);
}