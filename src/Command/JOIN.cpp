#include "../../includes/Command/Command.hpp"
#include "../../includes/Network/Channel.hpp"
#include "../../includes/Network/Client.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>   // Para std::setw y std::setfill
#include <unistd.h>  // Para el envío de sockets y error handling
#include <cstring>
#include <errno.h>  // Para errno y strerror


//JOIN #channel or JOIN #channel1, #channel2 or JOIN #channel passsword

#include "../../includes/Command/Command.hpp"
#include "../../includes/Network/Channel.hpp"
#include "../../includes/Network/Client.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cstring>  // Para `strerror`
#include <errno.h>   // Para `errno`

// Manejo del comando JOIN
void handleJoin(Client *client, Server *server)
{
    (void)server;
    const std::vector<std::string> &args = client->getArgs();

    if (args.empty() || args[0][0] != '#' || args[0].size() == 1) 
    {
        std::string errorMsg = "ERROR: JOIN command requires a channel name.\r\n";
        send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        return;
    }

    for (size_t i = 0; i < args.size(); ++i) 
    {
        const std::string &channelName = args[i];

        // Obtener o crear el canal
        Channel* channel = Channel::getOrCreateChannel(channelName);

        if (channel == NULL) {
            std::string errorMsg = "ERROR: Unable to join channel " + channelName + ".\r\n";
            send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
            continue;
        }

        if (channel->addMember(*client)) {
            // Confirmar que el cliente se unió al canal
            std::string successMsg = ":irc.myserver.com JOIN #" + channelName + "\r\n";
            send(client->getSocket(), successMsg.c_str(), successMsg.size(), 0);

            // Enviar mensaje RPL_NAMES para informar a HexChat sobre los usuarios en el canal
// En tu método handleJoin después de agregar al cliente al canal
            std::ostringstream namesStream;
            namesStream << ":irc.myserver.com 353 " << client->getNickName()
                        << " = #" << channelName << " :";

            const std::set<Client*>& members = channel->getMembers();
            for (std::set<Client*>::const_iterator it = members.begin(); it != members.end(); ++it) {
                namesStream << (*it)->getNickName() << " ";
            }

            std::string rplNamesMsg = namesStream.str();
            send(client->getSocket(), rplNamesMsg.c_str(), rplNamesMsg.size(), 0);

            // Mensaje opcional para finalizar la lista de nombres
            std::string endOfNamesMsg = ":irc.myserver.com 366 " + client->getNickName() +
                                        " #" + channelName + " :End of NAMES list.\r\n";
            send(client->getSocket(), endOfNamesMsg.c_str(), endOfNamesMsg.size(), 0);


        } else {
            std::string errorMsg = "ERROR: You are already in the channel " + channelName + ".\r\n";
            send(client->getSocket(), errorMsg.c_str(), errorMsg.size(), 0);
        }
    }
}


