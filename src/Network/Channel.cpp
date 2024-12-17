#include "../../includes/Network/Channel.hpp"

Channel::Channel(const std::string& name): _name(name), _clientLimitMode(0), _clientLimit(0), _key("") //, _inviteOnlyMode(0),
// _clientLimitMode(0), _keyMode(0), _protectedTopicMode(1), _clientLimit(0)
{
    std::cout << "Channel object created" << std::endl;
}

Channel::~Channel() 
{
    std::cout << "Channel object destroyed" << std::endl;
}

 std::string const &Channel::getName() const 
{
    return _name;
}

bool Channel::addMember(Client &client)
{
    if (_members.find(&client) != _members.end())
    {
        return false; //already member
    }
    _members.insert(&client);
    return true;
}

void Channel::removeMember(Client &client)
{
    _members.erase(&client);
}

void Channel::broadcast(const Client &sender, const std::string &message)
{
    for (std::set<Client*>::iterator it = _members.begin(); it != _members.end(); ++it)
    {
        if (*it != &sender)
        {
            send((*it)->getSocket(), message.c_str(), message.size(), 0);
        }
    }
}

Channel *Channel::getOrCreateChannel(const std::string& channelName)
{
    std::map<std::string, Channel*>::iterator it = _channels.find(channelName);
    if (it != _channels.end())
    {
        return (it->second);  // existing channel
    }

    // Create a new channel if necessary
    Channel *newChannel = new Channel(channelName);
    _channels[channelName] = newChannel;
    std::cout << "Created new channel: " << channelName << std::endl;  // Debugging message
    return newChannel;
}

// catch an existing channel
Channel* Channel::getChannel(const std::string& channelName)
{
    std::map<std::string, Channel*>::iterator it = _channels.find(channelName);
    if (it != _channels.end())
    {
        return (it->second);  
    }
    return NULL;  // Channel not found
}

bool Channel::isMember(Client const &client) const 
{
    return _members.find(const_cast<Client*>(&client)) != _members.end();
}

void Channel::sendTopic(Client &client)
{
    std::string response;

    if (this->_topic.empty())  // If no topic is set
    {
        response = ":" + client.getNickName() + " 331 " + this->_name + " :No topic is set\r\n";
    }
    else  // Send the existing topic
    {
        response = ":" + client.getNickName() + " 332 " + this->_name + " :" + this->_topic + "\r\n";
    }

    send(client.getSocket(), response.c_str(), response.size(), 0);
}


const std::set<Client*>& Channel::getMembers() const
{
    return _members;
}

void Channel::setKey(std::string const &key)
{
    _key = key;
}

std::string const &Channel::getKey() const
{
    return _key;
}

void Channel::setClienLimitMode(bool mode)
{
    _clientLimitMode = mode;
}

bool Channel::getClientLimitMode() const
{
    return _clientLimitMode;
}

// std::set<Client*> &Channel::getMembers() const
// {
//     return _members;
// }

void Channel::setClientLimit(size_t limit)
{
    _clientLimit = limit;
}

size_t Channel::getClientLimit() const
{
    return _clientLimit;
}

void Channel::sendNamesList(Client &client)
{
    std::string response = ":" + client.getNickName() + " 353 " + client.getNickName() + " = " + this->_name + " :";

    // Append all nicknames of members in the channel
    for (std::set<Client*>::iterator it = this->_members.begin(); it != this->_members.end(); ++it)
    {
        response += (*it)->getNickName() + " ";
    }

    // Trim the trailing space from the list manually (C++98 way)
    if (!response.empty() && response[response.size() - 1] == ' ')
    {
        response.resize(response.size() - 1);  // Remove the last space
    }

    response += "\r\n";

    // End of names list (RPL_ENDOFNAMES 366)
    response += ":" + client.getNickName() + " 366 " + this->_name + " :End of /NAMES list\r\n";

    send(client.getSocket(), response.c_str(), response.size(), 0);
}








