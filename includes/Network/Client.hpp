#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <vector>

class Client
{
	private:
		int _socket;
		std::vector<std::string>_args; 
		std::string _nickname;
	public:
		Client(int sock);
		int getSocket() const;
		std::string getNickName() const;
		void setNickName(const std::string &newNick);
		std::vector<std::string> getArgs() const;
		void setArgs(const std::vector <std::string> &arguments);
};

#endif
