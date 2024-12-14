#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Client.hpp"
#include <set>
#include <map>
#include <sys/socket.h>


class Channel
{
	private:
		std::string			_name;
		// std::string		_type;
		std::string			_topic;
		std::set<Client*>	_members;
		// Client*				_operator;
		// bool				_inviteOnlyMode;
		// bool				_clientLimitMode;
		// bool				_keyMode;
		// bool				_protectedTopicMode;
		// int					_clientLimit;
		// std::string			_key;

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