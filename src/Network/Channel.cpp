#include "../../includes/Network/Channel.hpp"

std::map<std::string, Channel*> Channel::_channels; // to check why

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
    for (std::set<Client*>::iterator it = _members.begin(); it != _members.end(); ++it) //set<Client*> is a collection of pointers to Client objects, it's a loop walking to every element Client* of _members
    {
        if ((*it)->getSocket() == client.getSocket()) //(*it) dereferences the iterator to accss to the Client* pointer inside of _members
                                                      //it means that if the socket from the client comming from arg is the same as a client in _members, it returns true      
        {
            return true;
        }
    }
    return false;
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