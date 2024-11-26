#include <stdexcept> // std::runtime_error
#include <sys/socket.h> // for socket()
#include <sys/types.h> // for socket()
#include <vector> // std::vector
#include <iostream>
#include "Client.hpp"
#include <cstdlib> //std::atoi
#include <unistd.h> //close()


class Server
{
    private:
            int _Port;
            std::vector<Client> clients;
            int SerSocketFd; //-> server socket file descriptor
    
    public:
            void SerSocket();
            void ServerInit(int port);
            Server(int port);
            ~Server();

}; 
