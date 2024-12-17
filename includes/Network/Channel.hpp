#pragma once
#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Client.hpp"
#include <set>
#include <map>
#include <sys/socket.h>

class Client;


class Channel
{
	private:
		std::string			_name;
		// std::string		_type;
		std::string			_topic;
		std::set<Client*>	_members;
		// Client*				_operator;
		// bool				_inviteOnlyMode;
		bool				_clientLimitMode;
		// bool				_keyMode;
		// bool				_protectedTopicMode;
		size_t					_clientLimit;
		std::string			_key;

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

		const std::set<Client*>& getMembers() const;

		void setKey(std::string const &key);
		std::string const &getKey() const;

		void setClienLimitMode(bool mode);
		bool getClientLimitMode() const;

		// std::set<Client*> &getMembers() const;

		void setClientLimit(size_t limit);
		size_t getClientLimit() const;

		void sendTopic(Client &client);       // Sends RPL_TOPIC (332)
    	void sendNamesList(Client &client);   // Sends RPL_NAMREPLY (353)

};


#endif