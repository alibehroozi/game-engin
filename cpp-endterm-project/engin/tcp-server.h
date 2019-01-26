
#ifndef tcp_server_h
#define tcp_server_h

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>


using namespace std;

#define MAXPACKETSIZE 4096

class TCPServer
{
public:
    void setup(int port);
    void receive(void (*callback)(int));
    void Send(int socketClient, string msg);
    void detach();
    bool addEvent(std::string eventName, void (*callback)(int socketClient, std::string));
    
private:
    std::string _requestedEvent;
    std::vector<std::pair<std::string, void (*)(int socketClient, std::string)> > _events;
    char _msg[MAXPACKETSIZE];
    int _sockfd, _n, _pid;
    struct sockaddr_in _serverAddress;
    struct sockaddr_in _clientAddress;
    void * Task(int socketClient);

};


#endif

