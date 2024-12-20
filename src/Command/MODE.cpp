#include "../../includes/Command/Command.hpp"

/*
i = channel on invitation only
t = only operators can change the channel topic
k = channel protected by a password
o = operators management
l = numbers of users limitation */

void handleMode(Client *client, Server * server)  
{
    (void)server; 
    (void)client;
    std::cout << "Handling MODE\n";
    // std::vector<std::striing> args = client->getArgs();
    // std::map<std::string, void(*)(Client *, Server *)> modes;
}