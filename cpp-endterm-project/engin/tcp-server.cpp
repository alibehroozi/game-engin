#include "tcp-server.h"

void TCPServer::setup(int port){
    _requestedEvent = "";
    _sockfd=socket(AF_INET,SOCK_STREAM,0);
    _serverAddress.sin_family=AF_INET;
    _serverAddress.sin_port=htons(port);
    
    ::bind(_sockfd,(struct sockaddr *)&_serverAddress, sizeof(_serverAddress));
    listen(_sockfd,SOMAXCONN);
}

void TCPServer::receive(void (*callback)(int)){
    while(1){
        int _newsockfd;
        socklen_t sosize  = sizeof(_clientAddress);
        _newsockfd = accept(_sockfd,(struct sockaddr*)&_clientAddress,&sosize);
        callback(_newsockfd);
        inet_ntoa(_clientAddress.sin_addr);
        Task(_newsockfd);
    }
}



void TCPServer::Send(int socketClient, string msg){
    send(socketClient,msg.c_str(),msg.length(),0);
}

void TCPServer::detach(){
    close(_sockfd);
}

bool TCPServer::addEvent(std::string eventName, void (*callback)(int socketClient, std::string)){
    std::pair<std::string, void (*)(int socketClient, std::string)> pair(eventName, callback);
    _events.push_back(pair);
    return true;
}

void * TCPServer::Task(int socketClient){
    ssize_t n;
    int newsockfd = socketClient;
    char msg[MAXPACKETSIZE];
    while(1){
        n=recv(newsockfd,msg,MAXPACKETSIZE,0);
        if(n==0){
            close(newsockfd);
            break;
        }
        msg[n]=0;
        puts("r=>\n");
        puts(msg);
        stringstream ss;
        string target;
        ss << msg;
        ss >> target;
//        puts(target.c_str());
        if(_requestedEvent == ""){
            _requestedEvent = target;
        }else{
            string reqEvent = _requestedEvent;
            _requestedEvent = "";
            for(int i = 0;i < _events.size();i++){
                if(_events[i].first == reqEvent){
                    (_events[i].second)(socketClient, target);
                }
            }
            
        }
    }
    return 0;
}
