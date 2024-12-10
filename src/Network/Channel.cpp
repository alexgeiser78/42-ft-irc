#include "../../includes/Network/Channel.hpp"

std::map<std::string, Channel*> Channel::_channels; // to check why

Channel::Channel(const std::string& name) : _name(name) 
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
        return (it->second);  // Canal existant
    }

    // Créer un nouveau canal si nécessaire
    Channel *newChannel = new Channel(channelName);
    _channels[channelName] = newChannel;
    return newChannel;
}

// Récupérer un canal existant
Channel* Channel::getChannel(const std::string& channelName)
{
    std::map<std::string, Channel*>::iterator it = _channels.find(channelName);
    if (it != _channels.end())
    {
        return (it->second);  // Retourne le canal existant
    }
    return NULL;  // Canal non trouvé
}
