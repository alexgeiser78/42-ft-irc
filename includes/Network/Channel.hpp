#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Client.hpp"
#include <set>
#include <map>
#include <sys/socket.h>
#include <sstream>


class Channel
{
	private:
		std::string			_name;
		std::string			_topic;
		std::set<Client*>	_members;

		std::set<Client*>	_invited;
		std::set<Client*>	_operator;
		bool				_inviteOnlyMode;
		bool				_clientLimitMode;
		bool				_keyMode;
		bool				_protectedTopicMode;
		size_t				_clientLimit;
		std::string			_key;

		static std::map<std::string, Channel*> _channels;
	
	public:
		Channel(const std::string& name);
		~Channel();
		std::string const &getName();
		// bool addMember(Client &client);
		void removeMember(Client &client);
		void broadcast(const Client &sender, const std::string &message);

		// static Channel *getOrCreateChannel(std::string const &channelName);
		static Channel *getChannel(const std::string &channelName);
		bool isMember(Client const &client) const;
		std::set<Client*> &getMembers();

		void setKey(std::string const &key);
		std::string const &getKey() const;

		void setClienLimitMode(bool mode);
		bool getClientLimitMode() const;

		void setClientLimit(size_t limit);
		size_t getClientLimit() const;

		void setOperator(Client *client);
		Client *getOperator() const;

		void setKeyMode(bool mode);
		bool getKeyMode() const;

		void 	setTopic(Client &client, const std::string &newTopic);
		std::string const &getTopic() const;

		void addInvited(Client *client);
		std::set<Client *> getInvited(void) const;

		void setInviteOnlyMode(bool mode);
		bool getInviteOnlyMode() const;
		std::string stringMembers(void);

		void sendTopic(Client &client);
		bool 	isOperator(const Client &client) const;
};


#endif