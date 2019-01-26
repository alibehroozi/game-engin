#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include "xo-events.h"
#include "../engin/tcp-server.h"

vector<pair<int,XOGame *> > XOEvents::xo_games;
TCPServer *XOEvents::tcpServer;

void XOEvents::startEngin(int port){
    tcpServer = new TCPServer();
    tcpServer->setup(port);
    XOEvents::registerEvents();
    tcpServer->receive(&newClient);
}

void XOEvents::startGameEvent(int socketClient, std::string data){
    puts("started");
    xo_games[getGameIndex(socketClient)].second->startGame();
}

int XOEvents::getGameIndex(int socketClient){
    int index = 0;
    for(int i = 0;i<xo_games.size();i++){
        if(xo_games[i].first == socketClient){
            index = i;
        }
    }
    return index;
}

void XOEvents::newClient(int socketClient){
    puts("newc");
    XOGame *xo_game = new XOGame(socketClient);
    pair<int,XOGame *> gamePair(socketClient, xo_game);
    xo_games.push_back(gamePair);
    xo_game->configure();
}

void XOEvents::resetGame(int socketClient, std::string data){
    puts("reset");
    xo_games.erase(xo_games.begin() + getGameIndex(socketClient));
    XOGame *xo_game = new XOGame(socketClient);
    pair<int,XOGame *> gamePair(socketClient, xo_game);
    xo_games.push_back(gamePair);
    xo_game->configure();
}

void XOEvents::endGameEvent(int socketClient, std::string data){
    xo_games[getGameIndex(socketClient)].second->endGame();
}
void XOEvents::getGameStatusEvent(int socketClient, std::string data){
    string toEmit = xo_games[getGameIndex(socketClient)].second->emitGameStatus();
    tcpServer->Send(socketClient, toEmit);

}
void XOEvents::setCellEvent(int socketClient, std::string data){
    puts("setcell");
    puts(data.c_str());
    std::string token;
    char delimiter = ',';
    std::istringstream tokenStream(data);
    int i = 0;
    int x = 0;
    int y = 0;
    char val = 0;
    while (std::getline(tokenStream, token, delimiter)){
        if(i == 0){
            x = stoi(token);
        }
        if(i == 1){
            y = stoi(token);
        }
        if(i == 2){
            val = token.c_str()[0];
        }
        i++;
    }
    char oldVal = xo_games[getGameIndex(socketClient)].second->getCells()[(x-1)*3 + y - 1].getValue();
    if(oldVal != 'x' && oldVal != 'y'){
        xo_games[getGameIndex(socketClient)].second->setCell(x, y, val);
    }
    xo_games[getGameIndex(socketClient)].second->checkGameEnded();
}
void XOEvents::getAllCellsEvent(int socketClient, std::string data){
    puts("getall");
    puts(data.c_str());
    string toEmit = xo_games[getGameIndex(socketClient)].second->emitCells();
    tcpServer->Send(socketClient, toEmit);
}

void XOEvents::addPlayerEvent(int socketClient, std::string data){
    xo_games[getGameIndex(socketClient)].second->addPlayer(data);
}


void XOEvents::registerEvents(){
    tcpServer->addEvent("startGame", &startGameEvent);
    tcpServer->addEvent("endGame", &endGameEvent);
    tcpServer->addEvent("getGameStatus", &getGameStatusEvent);
    tcpServer->addEvent("setCell", &setCellEvent);
    tcpServer->addEvent("getAllCells", &getAllCellsEvent);
    tcpServer->addEvent("addPlayer", &addPlayerEvent);
    tcpServer->addEvent("resetGame", &resetGame);
}
