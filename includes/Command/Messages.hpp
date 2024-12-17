#define once

#define ENDL "\r\n"

#define ERR_NEEDMOREPARAMS(commmand) (command + " :Not enough parameters" + ENDL)

//NICK
#define ERR_NONICKNAMEGIVEN(nickname) (nickname + " :No nickname given" + ENDL)
#define ERR_ERRONEUSNICKNAME(nickname, nick) (nickname + " " + nick + " :Erroneus nickname" + ENDL)
#define ERR_NICKNAMEINUSE(nickname, nick) (nickname + " " + nick + " :Nickname is already in use" + ENDL)
#define RPL_NICK(nickname, nick) (nickname + " changed nickname to " + nick + ENDL)

#define ERR_BADCHANNELKEY(channel) (channel + " :Cannot join channel (+k)" + ENDL)

#define RPL_JOINMSG(nickname, username, hostname, channel) (":" + nickname + "!" + username + "@" + hostname + " JOIN " + channel + ENDL)