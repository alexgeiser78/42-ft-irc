#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Client.hpp"
#include <set>
#include <map>
#include <sys/socket.h>


class Channel
{
    private:
        std::string _name;
        std::set<Client*> _members;

        static std::map<std::string, Channel*> _channels;
    
    public:
        Channel(const std::string& name);
        ~Channel();
        std::string const &getName() const;
        bool addMember(Client &client);
        void removeMember(Client &client);
        void broadcast(const Client &sender, const std::string &message);

        static Channel *getOrCreateChannel(std::string const &channelName);
        static Channel *getChannel(std::string const &channelName);
        bool isMember(Client const &client) const;
};


#endif