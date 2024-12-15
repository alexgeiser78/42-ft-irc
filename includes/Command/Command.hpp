#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <vector>
#include <map>
#include <sys/socket.h> //send() recv()
#include "../Network/Client.hpp"
// #include "../Network/Server.hpp"
#include <cctype> //std::isalnum

#define SERVER_VERSION "ircserv-1.0"
#define NETWORK_NAME "MyIRCNetwork"
#define SERVER_NAME "irc.myserver.com"
#define CHANNEL_MODES "oitkl"
#define PARAM_MODES "o,k"

class Server;

// command functions declaration
void handleInvite(Client *client, Server * server);
void handleJoin(Client *client, Server * server);
void handleKick(Client *client, Server * server);
void handleMode(Client *client, Server * server);
void handleNick(Client *client, Server * server);
void handlePart(Client *client, Server * server);
void handlePrivMsg(Client *client, Server * server);
void handleTopic(Client *client, Server * server);
void handleUser(Client *client, Server * server);
// class Server;

class Command //assiciate a command to a function
{
    private:
        std::map<std::string, void(*)(Client *, Server *)> commands;
        // std::vector<std::string>_args;
        //assoc container, key is the command given by the user [INVITE], value is a pointer to the function that will handle the command
    public:
        Command(); //constructor to initiate the map
        ~Command();

        void        executeCommand(const std::string& commandName, Client *client, Server *server); //execute the command

        // std::vector<std::string>    args;
};

#endif

