#include "../../includes/Command/Command.hpp"
#include "../../includes/Command/Messages.hpp"
#include "../../includes/Network/Channel.hpp"
#include "../../includes/Network/Server.hpp"

//PRIVMSG <receiver> :<message>
//<receiver> could be a user or a channel

void handlePrivMsg(Client *client, Server * server)  
{
    const std::vector<std::string>& args = client->getArgs();
    

    (void)server; 
    std::cout << "Handling PrivMsg\n";

    //check args
    if (args.size() < 2) 
    {
        std::string errorMsg = PREFIX_SERVER + ERR_NORECIPIENT("PRIVMSG");
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        std::cerr << "Error: No recipient specified for PRIVMSG\n";
        return;
    }

    //cath args
    std::string receiver = args[0];
    std::string message = args[1];
    std::cout << "receiver " << receiver << std::endl;
    std::cout << "message " << message << std::endl;

    //check msg
    if (message.empty()) 
    {
        std::string errorMsg = PREFIX_SERVER + ERR_NOTEXTTOSEND;
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        std::cerr << "Error: No text to send for PRIVMSG\n";
        return;
    }

    Channel *channel = NULL;

    // check channel
    if (receiver[0] == '#') //if it's a channel
    {
        //find channel
        channel = server->findChannel(receiver);
        if (!channel) 
        {
            std::string errorMsg = PREFIX_SERVER + ERR_NOSUCHCHANNEL(client->getNickName(), receiver);
            send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
            std::cerr << "Error: No such channel " << receiver << "\n";
            return;
        }
    

        // and check permission
        if (!channel->isMember(client)) 
        {
            std::string errorMsg = PREFIX_SERVER + ERR_CANNOTSENDTOCHAN(receiver);
            send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
            std::cerr << "Error: Cannot send to channel " << receiver << "\n";
            return;
        }

        // Send MSG to all members
        std::string formattedMsg = ":" + client->getNickName() + " PRIVMSG " + receiver + " :" + message + ENDL;
        channel->broadcast(client, formattedMsg);
        std::cout << "Message sent to channel " << receiver << ": " << message << "\n";
    }

    else 
    { // or it's a user
        Client *targetClient = server->findClient(receiver);
        if (!targetClient) //if the user doesn't exist
        {
            std::string errorMsg = PREFIX_SERVER + ERR_NOSUCHNICK(receiver);
            send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
            std::cerr << "Error: No such nick " << receiver << "\n";
            return;
        }

        // Send MSG to User
        std::string formattedMsg = ":" + client->getNickName() + " PRIVMSG " + receiver + " :" + message + ENDL;
        send(targetClient->getSocket(), formattedMsg.c_str(), formattedMsg.size(), 0);
        std::cout << "Message sent to user " << receiver << ": " << message << "\n";
    }
}