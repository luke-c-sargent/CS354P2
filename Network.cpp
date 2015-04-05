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
using std::hex;

Network::Network(int state,BaseApplication* bap):
    connected(0),
    baseapp(bap)
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
    cout << "NET: I am a server\n===================\n";
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

    baseapp->insertP2();
    connected=true;


    //close(serversockfd);
    //close(clientsockfd);

}

void Network::searchForConnection(int portno, std::string networkName)
{
  cout << "NET: I am a client\n===================\n";


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

    bzero(buffer,256);

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
    baseapp->insertP2();
    connected=true;

}

bool Network::sendPacket(int len)
{
    int n;

    if(strlen(toSendPacket)>len)
      len=strlen(toSendPacket);

    n = write(clientsockfd, toSendPacket, len);

    if( n < 0 )
    {
        error("Error sending data from socket");
        return false;
    }

    //Packet sent, zero out toSendPacket buffer
    bzero(toSendPacket, 256);
    //sendPacketReady = false;

    return true;

}

void Network::printpacket(char * cp)
{
  for(int i=0; i < 32; i++){
    cout << hex << (int)((unsigned char)cp[i]) <<"_";
  }
  cout <<"\n";
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

void Network::setState(int in){
  if(in==0)
    curState=GAME_SINGLE;
  else if(in==1)
    curState=GAME_SERVER;
  else if(in==2)
    curState=GAME_CLIENT;
}

//setAddress function
