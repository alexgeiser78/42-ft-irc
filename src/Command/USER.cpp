#include "../../includes/Command/Command.hpp"

//USER <username> <hostname> <servername> :<realname>

void handleUser(Client *client) 
{ 
    std::cout << "Handling USER\n";
    const std::vector<std::string>& args = client->getArgs();

    if (args.size() < 4)
    {
        std::string errorMsg = "ERROR: USER command requires at least 4 arguments\n";
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        std::cerr << "Client " << client->getSocket() << ": Invalid USER command\n";
        return;
    }

    if (client->isRegistered())
    {
        std::string errorMsg = "ERROR: USER command can only be used once\n";
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        std::cerr << "Client " << client->getSocket() << errorMsg << std::endl;
        return;
    }

    std::string username = args[0];
    std::string hostname = args[1];
    std::string servername = args[2];
    std::string realname = args[3];

    client->setUsername(username);
    client->setHostname(hostname);
    client->setServername(servername);
    client->setRealname(realname);

    client->setRegistered(true);

    std::string successMsg = "USER command processed successfully. Welcome, " + username + "!\n";
    send(client->getSocket(), successMsg.c_str(), successMsg.size(), 0);
    std::cout << "Client " << client->getSocket() << ": USER command processed successfully\n";
    
    }