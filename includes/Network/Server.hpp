#pragma once
#ifndef SERVER_HPP
#define SERVER_HPP

#include <stdexcept> //std::runtime_error
#include <sys/types.h> //socket()
#include "../Command/Command.hpp"
#include "Channel.hpp"
#include <cstdlib> //std::atoi
#include <unistd.h> //close()
#include <csignal> //signal()
#include <netinet/in.h> //sockaddr_in and in_addr
#include <poll.h> //poll()
#include <fcntl.h> //fcntl()
#include <string> //std::string
#include <ctime> //time()
#include <arpa/inet.h> //inet_ntoa
#include <cstring> //memset

class Command;
class Channel;


class Server
{
    private:
		int 	_Port;
		std::map<int, Client> clients2;
		int 	SerSocketFd; //server socket file descriptor
	    std::vector <struct pollfd> FD; //file descriptor structure
	    std::string _Password;
	    std::string _ServerCreationTime;
		std::vector<Channel *> channels;

    public:
	    Server(int port, std::string password);
	    ~Server();
		void 					setServerCreationTime(void);
	    std::string 			getServerCreationTime(void) const;
	    void 					SerSocket();
	    static void 			SignalHandler(int signum);
	    void 					ServerInit(int port);
	    void 					CloseFDs();
	    static bool 			Signal;
	    void        			AcceptNewClient(void);
	    void        			RemoveClient(int fd);
	    void        			RecieveData(int fd);
	    void        			ProccessCommand(int fd, std::string line);

		std::vector<Channel *>	&getChannels(void);
		void					addChannel(Channel *channel);

		Channel 				*findChannel(const std::string &channelName);
		Client*					findClient(const std::string& nickname);
		std::map<int, Client> 	&getClients();
};

/*HOW WORKS sockaddr_in and in_addr:

struct sockaddr_in //adress struct for IPv4
{
	sa_family_t     sin_family; //address family (always AF_INET for IPv4), used to determine the format of the address
	in_port_t       sin_port; //16 bit integer representing the port number, must be converted to network byte order using htons() function, (big endian)
	struct  in_addr sin_addr; //32 bit integer representing the IP address, must be converted to network byte order using inet_addr() function, INADDR_ANY is used for binding to all local interfaces
	char            sin_zero[8]; //Not used, must be zero, used for mainting structure size
};

struct in_addr //structure representing the IP address
{
	uint32_t s_addr; //32 bit integer representing the IP address, network byte order
};
*/

/*HOW WORKS pollfd:
struct pollfd //structure is used to describe a set of file descriptors to be monitored by the poll() function
{
	int fd; //file descriptor to be monitored (socket)
	short events; //monitored events, pollin, pollout, pollerr, pollhup, pollnval
	short revents; //detected events (results)
};*/

//poll() function: waits for one of a set of file descriptors to become ready to perform I/O 
//int poll(struct pollfd fds[], nfds_t nfds, int timeout)
//fds[]: array of pollfd structures
//nfds: number of elements in the fds array
//timeout: time to wait in milliseconds, -1 means wait indefinitely, 0 means poll() will return immediately


#endif
