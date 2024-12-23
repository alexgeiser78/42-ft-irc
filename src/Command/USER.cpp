#include "../../includes/Command/Command.hpp"
#include "../../includes/Command/Messages.hpp"

//USER <username> <hostname> <servername> :<realname>
///USER testuser localhost irc.example.com :Test User

void handleUser(Client *client, Server * server) 
{
    (void)server; 
    std::cout << "Handling USER\n";
    const std::vector<std::string>& args = client->getArgs();
    
    // argprint
    std::cout << "Argumentos: ";
    for (size_t i = 0; i < args.size(); ++i) 
    {
        std::cout << args[i] << " ";
    }
    std::cout << std::endl;

    if (client->isRegistered())
    {
        std::string errorMsg = PREFIX_SERVER + ERR_ALREADYREGISTERED(client->getNickName());
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        std::cerr << "Client " << client->getSocket() << errorMsg << std::endl;
        return;
    }
    
    if (args.size() < 4)
    {
        std::string errorMsg = PREFIX_SERVER + ERR_NEEDMOREPARAMS("USER");
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        std::cerr << "Client " << client->getSocket() << ": Invalid USER command\n";
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

    // std::string successMsg = "USER command processed successfully. Welcome, " + username + "!\n";
    // send(client->getSocket(), successMsg.c_str(), successMsg.size(), 0);
    // std::cout << "Client " << client->getSocket() << ": USER command processed successfully\n";
    // std::cout << "In USER, before conditional, client is registered: " << client->isRegistered() << std::endl;
    if (!client->isRegistered() && !client->getNickName().empty())
    {
        client->setRegistered(true);
        std::string successMsg1 = RPL_WELCOME(client->getNickName(), client->getUsername(), client->getHostname());
        send(client->getSocket(), successMsg1.c_str(), successMsg1.size(), 0);
        std::cout << successMsg1;
        std::string successMsg2 = RPL_YOURHOST(client->getNickName());
        std::cout << successMsg2;
        send(client->getSocket(), successMsg2.c_str(), successMsg2.size(), 0);
        std::string successMsg3 = RPL_CREATED(client->getNickName());
        std::cout << successMsg3;
        send(client->getSocket(), successMsg3.c_str(), successMsg3.size(), 0);
        std::string successMsg4 = RPL_MYINFO(client->getNickName());
        std::cout << successMsg4;
        send(client->getSocket(), successMsg4.c_str(), successMsg4.size(), 0);
    }
    return;
}
