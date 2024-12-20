#define once

#define ENDL "\r\n"

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