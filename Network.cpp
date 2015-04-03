#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "BaseApplication.h"

using std::cout;

Network::Network(int state):
    connected(0)
{

    //1: server, 2: client, 3: single
    if (state == 1) {
        curState = GAME_SERVER;
    }
    else if (state == 2) {
        curState = GAME_CLIENT;
    }
    else {
        curState = GAME_SINGLE;
    }

    //store network address
}

void error(const char *msg)
{
    perror(msg);
    exit(1);
}
void Network::waitForConnection(int portno)
{
    //cout << "\n\n\n\n\n\n@@@@@@@@@@@@@@@@@@@@@@@ inside waitForConnection@@@@@@@@@@@@@@@@@@@@\n\n\n\n\n\n\n";
    int portnum;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    serversockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (serversockfd < 0)
        error("ERROR opening socket");

    struct timeval timeout;
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;

        if (setsockopt (serversockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
                    sizeof(timeout)) < 0)
            error("setsockopt failed\n");

        if (setsockopt (serversockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,
                    sizeof(timeout)) < 0)
            error("setsockopt failed\n");

    bzero((char *) &serv_addr, sizeof(serv_addr));

    portnum = portno;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);


    //Bind socket to server IP address?
    if (bind(serversockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    //Listen for connection request
    listen(serversockfd,5);

    clilen = sizeof(cli_addr);
    //Accept client connection request and assign new socket file descriptor
    clientsockfd = accept(serversockfd, (struct sockaddr *) &cli_addr, &clilen);

    if (clientsockfd < 0)
        error("ERROR on accept");

    bzero(buffer,256);

    n = read(clientsockfd,buffer,255);
    std:: string message(buffer);
    if (n < 0) error("ERROR reading from socket");

    //cout << "\n\n\nHere is the message: " << message << "\n\n\n";

    connected=true;


    //close(serversockfd);
    //close(clientsockfd);

}

void Network::searchForConnection(int portno, std::string networkName)
{

    int portnum, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    portnum = portno;
    clientsockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (clientsockfd < 0)
        error("ERROR opening socket");

    char url[networkName.length()+1];
    strcpy(url, networkName.c_str());

    server = gethostbyname(url);

    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

    serv_addr.sin_port = htons(portno);

    if (connect(clientsockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    /*printf("Please enter the message: ");
*/
    bzero(buffer,256);
    /*fgets(buffer,255,stdin);
    buffer[0]='H';
    buffer[1]='i';
    buffer[2]='!';
    buffer[3]='\n';
*/
    n = write(clientsockfd,buffer,strlen(buffer));

    if (n < 0)
        error("ERROR writing to socket");

    bzero(buffer,256);

    //n = read(clientsockfd,buffer,255);

    if (n < 0)
        error("ERROR reading from socket");

    //printf("%s\n",buffer);

    //cout << "\n\n\n\n\n\n@@@@@@@@@@@@@@@@@@@@@@@ inside searchForConnection @@@@@@@@@@@@@@@@@@@@\n\n\n\n\n\n\n";

    //close(clientsockfd);
    connected=true;

}

/*
void Network::writeSendBuffer(char buffer*)
{
    toSendPacket = strcpy(toSendPacket, buffer);
    //sendPacketReady = true;
}
*/

bool Network::sendPacket()
{
    int n;

    //if (sendPacketReady)
    //{
    n = write(clientsockfd, toSendPacket, strlen(toSendPacket));

    if( n < 0 )
    {
        error("Error sending data from socket");
        return false;
    }
    //}


    //Packet sent, zero out toSendPacket buffer
    bzero(toSendPacket, 256);
    //sendPacketReady = false;

    return true;

}

bool Network::receivePacket()
{
    int n;

    bzero(toRecPacket,256);

    n = read(clientsockfd,toRecPacket,255);

    if( n < 0 )
    {
        error("Error reading data from socket");
        return false;
    }

    return true;
}

bool Network::closeConnections()
{
    //cout << "\n\nClosing client connection\n\n";
    /*
    if(close(serversockfd) < 0)
    {
        error("Didn't close server socket");
    }
    else if(close(clientsockfd) < 0)
    {
        error("Didn't close client socket");
    }
    */

    if(this->curState ==GAME_CLIENT)
    {

        close(clientsockfd);

        return true;
    }
    else if (this->curState == GAME_SERVER)
    {
        cout << "\n\nClosing server connection\n\n";
        close(serversockfd);
        close(clientsockfd);
        return true;
    }
    else
    {
        return false;
    }
    connected=false;


}
//setAddress function
