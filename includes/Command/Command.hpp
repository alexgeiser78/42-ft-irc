#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <vector>
#include <map>
#include <sys/socket.h> //send() recv()
#include "../Network/Client.hpp"

// command functions declaration
void handleInvite(Client &client);
void handleJoin(Client &client);
void handleKick(Client &client);
void handleMode(Client &client);
void handleNick(Client &client);
void handlePart(Client &client);
void handlePrivMsg(Client &client);
void handleTopic(Client &client);
void handleUser(Client &client);

class Command //assiciate a command to a function
{
    private:
        std::map<std::string, void(*)(Client&)> commands;
        //assoc container, key is the command given by the user [INVITE], value is a pointer to the function that will handle the command
    public:
        Command(); //constructor to initiate the map
        ~Command();
        void executeCommand(const std::string& commandName, Client &client);
};

#endif

