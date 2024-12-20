#define once

#define ENDL "\r\n"
#define PREFIX_SERVER ":irc.myserver.com"

#define ERR_NEEDMOREPARAMS(commmand) (command + " :Not enough parameters" + ENDL)

//NICK
#define ERR_NONICKNAMEGIVEN(nickname) (nickname + " :No nickname given" + ENDL)
#define ERR_ERRONEUSNICKNAME(nickname, nick) (nickname + " " + nick + " :Erroneus nickname" + ENDL)
#define ERR_NICKNAMEINUSE(nickname, nick) (nickname + " " + nick + " :Nickname is already in use" + ENDL)
#define RPL_NICK(nickname, nick) (nickname + " changed nickname to " + nick + ENDL)

//JOIN
#define ERR_BADCHANNELKEY(channel) (channel + " :Cannot join channel (+k)" + ENDL)

#define RPL_JOINMSG(nickname, username, hostname, channel) (":" + nickname + "!" + username + "@" + hostname + " JOIN " + channel + ENDL)
#define ERR_INVITEONLYCHAN(channel) (channel + " :Cannot join channel (+i)" + ENDL)
#define ERR_CHANNELISFULL(channel) (channel + " :Cannot join channel (+l)" + ENDL)

#define RPL_TOPIC(nick, channel, topic) (" 332 " + nick + " " + channel + " :" + topic + ENDL)
#define RPL_NOTOPIC(nick, channel) (" 331 " + nick + " " + channel + " :No topic is set" + ENDL)
#define RPL_NAMREPLY(channel, nick, names) (" 353 " + nick + " = " + channel + " :" + names + ENDL)

//MODE
#define ERR_NEEDMOREPARAMS_MODE(nick) (" 461 " + nick + "MODE :Not enough parameters" + ENDL)
#define ERR_CHANOPRIVSNEEDED(nick, channel) (" 482 " + nick + " " +  channel + " :You're not channel operator" + ENDL)
#define ERR_UNKNOWNMODE() (":<server> 472 <nickname> <char> :is unknown mode char to me")
#define ERR_NOSUCHNICK(nickname, nick) (" 401 " + nickname + " " + nick + " :No such nick/channel" + ENDL)
#define ERR_KEYSET() (":<server> 467 <nickname> <channel> :Channel key already set")
#define ERR_NOSUCHCHANNEL(nick, channel) (" 403 " + nick + " " + channel + " :No such channel" + ENDL)
#define RPL_CHANNELMODEIS(nick, channel, modes) (" 324 " + nick + " " + channel + " " + modes + ENDL)
