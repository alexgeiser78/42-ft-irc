#include "../../includes/Command/Command.hpp"
#include "../../includes/Network/Server.hpp"
#include "../../includes/Command/Messages.hpp"


//TO SEE THE TOPIC:
//-request to server: TOPIC <channel>
//-answer from server if the channel contains a topic: :<server> 332 <nickname> <channel> :<topic>
//-answer form server without topic: :<server> 331 <nickname> <channel> :No topic is set
//TO DEFINE THE TOPIC:
//-request: TOPIC <channel> :<new_topic>
//-answer: :<nickname>!<user>@<host> TOPIC <channel> :<new_topic>




void handleTopic(Client *client, Server * server) 
{
     std::cout << "Handling TOPIC\n"; 
     
     const std::vector<std::string> &args = client->getArgs();

    // Check the args
    if (args.size() < 1 || args[0].empty()) 
    {
        std::string errorMsg = ERR_NEEDMOREPARAMS("TOPIC");
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        std::cout << "Error: Missing channel name for TOPIC command\n";
        return;
    }


    const std::string &channelName = args[0];
    std::cout << channelName <<std::endl;

    // search the channel via the server
    Channel *channel = server->findChannel(channelName);
    if (channel == NULL)
    {
        std::string errorMsg = ERR_NOSUCHCHANNEL(client->getNickName(), channelName);
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        std::cout << "Error: No such channel" << std::endl;
        return;
    }

    // Check if the client is a member of the channel
    if (!channel->isMember(client)) 
    {
        std::string errorMsg = ERR_NOTONCHANNEL(client->getNickName(), channelName);
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        std::cout << "Error: Client is not a member of the channel\n";
        return;
    }

    //sendig topic
    if (args.size() == 1)
    {
        channel->sendTopic(*client);
        std::cout << "Topic sent to client" << std::endl;
        return;
    }

    // Check if the topic starts with ':'
    std::string newTopic = args[1];

    // Ensure that there is no space between ':' and the topic content
    if (newTopic.empty() || newTopic[0] != ':') 
    {
        std::string errorMsg = ERR_TOPICNEEDSCOLON(client->getNickName());
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        std::cout << "Error: Topic must start with a ':'\n";
        return;
    }

    // Remove the ':' from the start of the topic (it's part of the IRC syntax)
    newTopic = newTopic.substr(1); // Remove the ':' character

    // Optionally, trim any leading or trailing spaces from the topic string
    newTopic.erase(0, newTopic.find_first_not_of(" \t")); // Trim the spaces at the beginning
    newTopic.erase(newTopic.find_last_not_of(" \t") + 1); // Trim the spaces at the end

    // Check if the topic is empty after trimming spacess
    if (newTopic.empty()) 
    {
        std::string errorMsg = ERR_EMPTYTOPIC(client->getNickName());
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        std::cout << "Error: Topic cannot be empty\n";
        return;
    }

    channel->setTopic(*client, newTopic);
    std::cout << "Topic chandeg to " << newTopic << std::endl;

}
/*
void Channel::setTopic(Client &client, const std::string &newTopic)
{
    // Check if the channel is protected (+t) and if the client is an operator
    if (this->_protectedTopicMode && !this->isOperator(client))
    {
        std::string errorMsg = "482 " + client.getNickName() + " " + this->_name + " :You're not a channel operator\r\n";
        send(client.getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        return;
    }

    // Define the topic
    this->_topic = newTopic;

    // Notify all users
    std::string notification = ":" + client.getNickName() + " TOPIC " + this->_name + " :" + this->_topic + "\r\n";
    for (std::set<Client *>::iterator it = this->_members.begin(); it != this->_members.end(); ++it)
    {
        send((*it)->getSocket(), notification.c_str(), notification.size(), 0);
    }
    std::cout << "Topic changed" << std::endl;
}
*/
bool Channel::isOperator(const Client &client) const
{
    return this->_operator.find(const_cast<Client*>(&client)) != this->_operator.end();
}
