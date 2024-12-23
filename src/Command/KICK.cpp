#include "../../includes/Command/Command.hpp"
#include "../../includes/Command/Messages.hpp"
#include "../../includes/Network/Channel.hpp"
#include "../../includes/Network/Client.hpp"
#include "../../includes/Network/Server.hpp"

// static void getChannelsAndUsers(Client *client, std::vector<std::string> &channels, std::vector<std::string> &users)
// {
//     std::stringstream streamChannels(client->getArgs()[0]);
//     std::stringstream streamUsers(client->getArgs()[1]);
//     std::string channel;
//     std::string user;
//     while (std::getline(streamChannels, channel, ','))
//     {
//         channels.push_back(channel);
//     }
//     while (std::getline(streamUsers, user, ','))
//     {
//         users.push_back(user);
//     }
// }

void handleKick(Client *client, Server * server)  
{
    (void)server;
    std::cout << "Handling KICK\n";
    if (client->getArgs().size() < 3)
    {
        std::string errorMsg = ERR_NEEDMOREPARAMS_P(client->getNickName(), "KICK");
        std::cout << errorMsg;
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        return;
    }
    // std::vector<std::string> &channels;
    // std::vector<std::string> &users;
    // getChannelsAndUsers(client, channels, users);
    // if (channels.size() == 1 && users.size() == 1)
    //     kickUserFromChannel(client, channels[0], users[0]);

}