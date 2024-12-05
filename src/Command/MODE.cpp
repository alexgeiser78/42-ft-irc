#include "../../includes/Command/Command.hpp"

/*
i = channel on invitation only
t = only operators can change the channel topic
k = channel protected by a password
o = operators management
l = numbers of users limitation */

void handleMode(Client &client)  
{ 
    (void)client;
    std::cout << "Handling MODE\n"; 
}