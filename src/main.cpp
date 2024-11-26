#include "../includes/network/Server.hpp"

int main (int argc, char **argv)
{
    if(argc != 3)
    {
        throw std::invalid_argument("Invalid number of arguments") ;
    }
    int port = std::atoi(argv[1]);
    if (port <= 0 || port > 65535) 
    { 
        std::cerr << "Error: Port must be between 1 and 65535." << std::endl;
        std::cerr << "Common Port for personnal server are between 1024 and 49151" << std::endl;
        return 1;
    }
    Server server(port);
    server.ServerInit(port);
}