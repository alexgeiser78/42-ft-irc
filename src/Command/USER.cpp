#include "../../includes/Command/Command.hpp"

//USER <username> <hostname> <servername> :<realname>

void handleUser(Client *client, Server * server) 
{
    (void)server; 
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
        std::string errorMsg = client->getNickName() + " :You may not reregister\n";
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

    // client->setRegistered(true);

    // std::string successMsg = "USER command processed successfully. Welcome, " + username + "!\n";
    // send(client->getSocket(), successMsg.c_str(), successMsg.size(), 0);
    // std::cout << "Client " << client->getSocket() << ": USER command processed successfully\n";
    // std::cout << "In USER, before conditional, client is registered: " << client->isRegistered() << std::endl;
    if (!client->isRegistered() && !client->getNickName().empty())
    {
        client->setRegistered(true);
        std::string successMsg1 = client->getNickName() + " :Welcome to the " + NETWORK_NAME + " Network, " + client->getNickName() + "[!" + client->getUsername() + "@" + client->getHostname() + "\n";
        send(client->getSocket(), successMsg1.c_str(), successMsg1.size(), 0);
        std::cout << successMsg1;
        std::string successMsg2 = client->getNickName() + " :Your host is " + SERVER_NAME + ", running version " + SERVER_VERSION "\n";
        std::cout << successMsg2;
        send(client->getSocket(), successMsg2.c_str(), successMsg2.size(), 0);
        std::string successMsg3 = client->getNickName() + " :This server was created " + client->getServerCreationTime() + "\n";
        std::cout << successMsg3;
        send(client->getSocket(), successMsg3.c_str(), successMsg3.size(), 0);
        std::string successMsg4 = client->getNickName() + " " + SERVER_VERSION + " " + CHANNEL_MODES + " " + PARAM_MODES + "\n";
        std::cout << successMsg4;
        send(client->getSocket(), successMsg4.c_str(), successMsg4.size(), 0);
    }
    return;
}
