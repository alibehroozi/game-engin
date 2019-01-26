
#ifndef xo_events_h
#define xo_events_h

#include "xo-game.h"
#include "../engin/tcp-server.h"
#include <vector>

class XOEvents{
public:
    static vector<pair<int,XOGame *> > xo_games;
    static TCPServer *tcpServer;
    static void startEngin(int port);
    static void startGameEvent(int socketClient, std::string data);
    static void endGameEvent(int socketClient, std::string data);
    static void getGameStatusEvent(int socketClient, std::string data);
    static void setCellEvent(int socketClient, std::string data);
    static void getAllCellsEvent(int socketClient, std::string data);
    static void addPlayerEvent(int socketClient, std::string data);
    static void resetGame(int socketClient, std::string data);
    static void registerEvents();
    static void newClient(int socketClient);
    static int getGameIndex(int socketClient);
};

#endif
