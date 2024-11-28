#include "../../includes/network/Server.hpp"

Server::Server(int port): _Port(port)
{
    this->_Port = port;
    std::cout << "Server object created" << std::endl;
}

Server::~Server()
{
    close(SerSocketFd);
    std::cout << "Server object destroyed" << std::endl;
}

void Server::SignalHandler(int signum)
{
    std::cout << "Interrupt signal (" << signum << ") received.\n";
    exit(signum);
}

void Server::ServerInit(int port)
{
	this->_Port = port;
	SerSocket(); //-> create the server socket

	std::cout <<"Server " << SerSocketFd << " Connected" << std::endl;
	std::cout << "Waiting to accept a connection...\n";
}

void Server::SerSocket()
{
    struct sockaddr_in addressIPv4;
    addressIPv4.sin_family = AF_INET;
    addressIPv4.sin_port = htons(this->_Port); //htons converts the unsigned short integer hostshort from host byte order to network byte order
    addressIPv4.sin_addr.s_addr = INADDR_ANY; //INADDR_ANY allows the server to accept a client connection on any interface
    
    SerSocketFd = socket(AF_INET, SOCK_STREAM, 0); //create a socket, AF_INET is the address family for IPv4, SOCK_STREAM is the type of socket, 0 is the protocol (default protocol related to the chosen type of socket)
    if (SerSocketFd == -1)
    {
        throw std::runtime_error("Failed to create a socket");
    }

    int reuseSocket = 1;
    if (setsockopt(SerSocketFd, SOL_SOCKET, SO_REUSEADDR, &reuseSocket, sizeof(reuseSocket)) == -1)
    {
        //int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);  add options to a socket
        //SOL_SOCKET is the level of the protocol,in this cse it means socket options apply to the socket itself
        //SO_REUSEADDR allows other sockets to bind to an address even if it is already in use or in the TIME_WAIT state
        //optval is a pointer to the value to be set
        //optlen is the size of the value to be set in bytes
        throw std::runtime_error("Failed to set socket options");
    }

    if (fcntl(SerSocketFd, F_SETFL, O_NONBLOCK) == -1)
    {
        //int fcntl(int fd, int cmd, ... /* arg */ ); manipulate file descriptor
        //fd is the file descriptor on which to operate
        //F_SETFL set the file status flags to the value specified by arg
        //O_NONBLOCK sets the file status flags and enables nonblocking mode, usful in case of poll() function to avoid blocking while waiting for events
        throw std::runtime_error("Failed to set socket to non-blocking mode");
    }

    if (bind(SerSocketFd, (struct sockaddr *)&addressIPv4, sizeof(addressIPv4)) == -1)
    {
        //int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen); soket function is just a communication endpoint, bind assigns the address specified by addr to the socket
        //sockfd is the file descriptor of the socket
        //addr is a pointer to a sockaddr structure containing the address to bind to, 0 will automatically assign the address to an available port 
        //addrlen is the size of the address structure
        throw std::runtime_error("Failed to bind the socket");
    }

    if (listen(SerSocketFd, SOMAXCONN) == -1)
    {
        //int listen(int sockfd, int backlog); listen for connections on a socket and make it a passive socket
        //sockfd is the file descriptor of the socket
        //backlog is the maximum length of the queue of pending connections
        //SOMAXCONN is the maximum value for backlog
        throw std::runtime_error("Failed to listen on the socket");
    }

    struct pollfd NewPoll;
    NewPoll.fd = SerSocketFd; //FD to be monitored
    NewPoll.events = POLLIN; //POLLIN set the event to read operation
    NewPoll.revents = 0; // revents is an output parameter, filled by the kernel with the events that actually occurred
    //fds.push_back(NewPoll); //-> add the server socket to the pollfd
}

void Server::CloseFDs()
{
    close(SerSocketFd);
    std::cout << "Server socket closed" << std::endl;
}

//active and passsive sockets
//active socket is the client socket, it initiates the connection to the server
//passive socket is the server socket, it waits for the client to initiate the connection
//when a connection request is received by the server socket, it creates a new socket for the client

