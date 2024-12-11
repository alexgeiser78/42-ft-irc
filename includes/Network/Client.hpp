#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <vector>
#include <unistd.h> // C librairy !!!!!!

class Client
{
	private:
		int _socket;
		std::vector<std::string>_args; 
		std::string _nickname;
		std::string _username;
		std::string _hostname;
		std::string _servername;
		std::string _realname;
		bool 		_isRegistered;

	public:
		Client(int sock);
		~Client();
		int getSocket() const;
		void closeClient();
		
		std::string getNickName() const;
		void setNickName(const std::string &newNick);
		
		std::vector<std::string> getArgs() const;
		void setArgs(const std::vector <std::string> &arguments);
		
		void setUsername(const std::string& username);
    	 std::string const &getUsername() const;

    	void setHostname(const std::string& hostname);
    	std::string const &getHostname() const;

    	void setServername(const std::string& servername);
    	std::string const &getServername() const;

    	void setRealname(const std::string& realname);
    	std::string const &getRealname() const;

		void setRegistered(bool isRegistered);
    	bool isRegistered() const;
};

#endif
