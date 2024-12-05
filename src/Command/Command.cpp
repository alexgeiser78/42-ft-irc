#include "../../includes/Command/Command.hpp"

Command::Command() //constructor
{
    std::cout << "Command object created" << std::endl;
    commands["INVITE"] = handleInvite;
    commands["JOIN"] = handleJoin;
    commands["KICK"] = handleKick;
    commands["MODE"] = handleMode;
    commands["NICK"] = handleNick;           
    commands["PART"] = handlePart;
    commands["PRIVMSG"] = handlePrivMsg;
    commands["TOPIC"] = handleTopic;
    commands["USER"] = handleUser;
}

Command::~Command() //destructor
{
    std::cout << "Command object destroyed" << std::endl;
}

void Command::executeCommand(const std::string& commandName, const std::vector<std::string>& args)
{
    if (commands.find(commandName) != commands.end()) //if the command is in the map
    {
        commands[commandName](args); //execute the function associated with the command
    }
    else
    {
        std::cerr << "Command not found" << std::endl;
    }
}
