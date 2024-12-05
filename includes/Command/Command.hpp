#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <vector>
#include <map>
#include "../Network/Client.hpp"

// command functions declaration
void handleInvite(const std::vector<std::string>& args);
void handleJoin(const std::vector<std::string>& args);
void handleKick(const std::vector<std::string>& args);
void handleMode(const std::vector<std::string>& args);
void handleNick(Client &client);
void handlePrivMsg(const std::vector<std::string>& args);
void handleTopic(const std::vector<std::string>& args);
void handleUser(const std::vector<std::string>& args);

class Command //assiciate a command to a function
{
    private:
        std::map<std::string, void(*)(const std::vector< std::string > &)> commands;
        //assoc container, key is the command given by the user [INVITE], value is a pointer to the function that will handle the command
    public:
        Command(); //constructor to initiate the map
        ~Command();
        void executeCommand(const std::string& commandName, const std::vector<std::string>& args);
};

#endif
