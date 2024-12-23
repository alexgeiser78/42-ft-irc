#define once

#define ENDL "\r\n"
#define PREFIX_SERVER ":irc.myserver.com"

#define ERR_NEEDMOREPARAMS(nick, channel) (" 461 " + nick + " " + channel + " :Not enough parameters" + ENDL)
#define ERR_CHANOPRIVSNEEDED(nick, channel) (" 482 " + nick + " " +  channel + " :You're not channel operator" + ENDL)
#define ERR_NOSUCHNICK(nick, channel, nickname) (" 401 " + nick + " " +  channel + " " + nickname + " :No such nick" + ENDL)

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
#define ERR_UNKNOWNMODE(nick, channel, char) (" 472 " + nick + " " + " " +  channel + " " + char + " :is unknown mode char to me" + ENDL)
#define ERR_UNKNOWNMODE_PARAM(nick, channel, param) (" 472 " + nick + " " + channel + " " + param + " :Invalid mode parameter" + ENDL)
#define ERR_KEYSET(nick, channel) (" 467 " + nick + " " + channel + " :Channel key already set" + ENDL)
#define ERR_NOSUCHCHANNEL(nick, channel) (" 403 " + nick + " " + channel + " :No such channel" + ENDL)
#define RPL_CHANNELMODEIS(nick, channel, modes) (" 324 " + nick + " " + channel + " " + modes + ENDL)

//INVITE

#define ERR_NOTONCHANNEL(nick, channel) (" 442 " + nick + " " + channel + " :You're not on that channel" + ENDL)
#define ERR_USERONCHANNEL(nick, nickname, channel) (" 443 " + nick + " " + nickname + " " + channel + " :is already on channel" + ENDL)
#define RPL_INVITING(nick, nickname, channel) (" 341 " + nick + " " + nickname + " " + channel + ENDL)
#define RPL_INVITED(nick, nickname, channel) (nick + " :" + nickname + " INVITE to " + channel + ENDL)
