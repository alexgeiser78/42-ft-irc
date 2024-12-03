#ifndef SERVER_HPP
#define SERVER_HPP

#include <stdexcept> //std::runtime_error
#include <sys/socket.h> //socket()
#include <sys/types.h> //socket()
#include <vector> // std::vector
#include <iostream>
#include "Client.hpp"
#include <cstdlib> //std::atoi
#include <unistd.h> //close()
#include <csignal> //signal()
#include <netinet/in.h> //sockaddr_in and in_addr
#include <poll.h> //poll()
#include <fcntl.h> //fcntl()

class Server
{
    private:
            int _Port;
            std::vector<Client> clients;
            int SerSocketFd; //server socket file descriptor
            std::vector <struct pollfd> FD; //file descriptor structure
            std::string _Password;
    public:
            Server(int port, std::string password);
            ~Server();
            void SerSocket();
            static void SignalHandler(int signum);
            void ServerInit(int port);
            void CloseFDs();
            static bool Signal;
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
