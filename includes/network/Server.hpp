#include <stdexcept> //std::runtime_error
#include <sys/socket.h> //socket()
#include <sys/types.h> //socket()
#include <vector> // std::vector
#include <iostream>
#include "Client.hpp"
#include <cstdlib> //std::atoi
#include <unistd.h> //close()
#include <csignal> //signal()


class Server
{
    private:
            int _Port;
            std::vector<Client> clients;
            int SerSocketFd; //-> server socket file descriptor
    
    public:
            Server(int port);
            ~Server();void SerSocket();
            static void SignalHandler(int signum);
            void ServerInit(int port);
            void CloseFDs();


}; 
