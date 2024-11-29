#include "../../includes/network/Server.hpp"

bool Server::Signal = false;

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
    Signal = true; //to stop the main loop
}

void Server::ServerInit(int port)
{
	this->_Port = port;   //-*-*-*-*--* to check, maybe has to be fix 
	SerSocket(); //create the server socket

	std::cout <<"Server " << SerSocketFd << " Connected" << std::endl;
	std::cout << "Waiting to accept a connection...\n";

    while(Server::Signal == false) //main loop
    {
        if ((poll(&FD[0], FD.size(), -1) == -1) && Server::Signal == false)
        {
            //&FD[0] is the address of the first element of the vector
            //-1 means wait indefinitely for an event
            throw std::runtime_error("poll() failed");
        }

        for(size_t i =0; i < FD.size(); i++) //iterate through the vector of pollfd structures
        {
            if (FD[i].revents & POLLIN) // if there is revents(returned events). Are flags writen in the FD after the call to poll()
                {
                if (FD[i].fd == SerSocketFd)  //.fd comes from poll.h
					{
                    std::cout << "Accepting new client function" << std::endl;
                    //AcceptNewClient(); //new connexion
                    }
                else
                    {
                    std::cout << "Receiving new data function" << std::endl;
                    //ReceiveNewData(FD[i].fd); //data from a connected client
                    }
                }   
        }
    }
    CloseFDs();
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

    struct pollfd NewPoll; //pollfd structure is used to describe a set of file descriptors to be monitored by the poll() function
                           //int poll(struct pollfd fds[], nfds_t nfds, int timeout)
                           //poll() function waits for one of a set of file descriptors to become ready to perform I/O
    NewPoll.fd = SerSocketFd; //FD to be monitored
    NewPoll.events = POLLIN; //POLLIN set the event to read operation
    NewPoll.revents = 0; // revents is an output parameter, filled by the kernel with the events that actually occurred
    FD.push_back(NewPoll); //add the new pollfd structure to the vector of pollfd structures
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
