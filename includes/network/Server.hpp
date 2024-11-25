#include <stdexcept> // std::runtime_error
#include <sys/socket.h> // for socket()
#include <sys/types.h> // for socket()
#include <vector> // std::vector
#include <iostream>
#include "Client.hpp"

class Server
{
    private:
            int Port;
            std::vector<Client> clients;
            int SerSocketFd; //-> server socket file descriptor
    
    public:
            void SerSocket();
            void ServerInit(int port);

}; 
