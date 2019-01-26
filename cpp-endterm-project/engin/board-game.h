#ifndef board_game_hpp
#define board_game_hpp


#include <string>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "cell.cpp"
#include "tcp-server.h"

struct SGameStatus{
    bool isGameEnded = false;
    bool isGameStarted = false;
    int winner = -1;
};

template <class CellType>
class BoardGame{
protected:
    int playersCount = 0;
    int boardSize[2] = {0,0};
    bool gameEnded = false;
    bool gameStarted = false;
    int new_socket = -1;
    int socketPort = 0;
    std::vector<Cell<CellType> > cells;
    std::vector<std::string> players;
    SGameStatus gameStatus;
    int socketClient;
public:
    BoardGame(int boardWidth, int boardHeight, int playersCount, int socketClient);
    bool setCell(int x, int y, CellType val);
    std::vector<Cell<CellType> > getCells();
    std::string emitCells();
    std::string emitGameStatus();
    bool addPlayer(std::string playerName);
    bool startGame();
    bool endGame();
    SGameStatus getGameStatus();
    virtual void configure() = 0;
    virtual void checkGameEnded() = 0;
};

#endif
