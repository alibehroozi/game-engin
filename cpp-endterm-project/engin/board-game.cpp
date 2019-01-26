#include "board-game.h"
#include "tcp-server.h"


template <class CellType>
BoardGame<CellType>::BoardGame(int boardWidth, int boardHeight, int playersCount, int socketClient){
    this->boardSize[0] = boardWidth;
    this->boardSize[1] = boardHeight;
    this->playersCount = playersCount;
    this->socketClient = socketClient;
    for(int i = 0;i<boardWidth*boardHeight;i++){
        Cell<CellType> cellObj;
        cells.push_back(cellObj);
    }
    
}


template <class CellType>
bool BoardGame<CellType>::setCell(int x, int y, CellType val){
    cells[(x-1)*boardSize[0] + y - 1].setValue(val);
    return true;
}

template <class CellType>
std::vector<Cell<CellType> > BoardGame<CellType>::getCells(){
    return cells;
}

template <class CellType>
string BoardGame<CellType>::emitCells(){
    std::string toEmit = "";
    std::string com = ",";
    for(int i = 0;i<this->boardSize[0]*this->boardSize[1];i++){
        toEmit = toEmit + cells[i].toString() + com;
    }
    return toEmit;
}

template <class CellType>
string BoardGame<CellType>::emitGameStatus(){
    std::string toEmit = "";
    std::string one = "1";
    std::string zero = "0";
    std::string com = ",";
    if(gameStatus.isGameEnded){
        toEmit = toEmit + one + com;
    }else{
        toEmit = toEmit + zero + com;
    }
    if(gameStatus.isGameStarted){
        toEmit = toEmit + one + com;
    }else{
        toEmit = toEmit + zero + com;
    }
    if(gameStatus.winner >= 0)
        toEmit = toEmit + players[gameStatus.winner] + com;
    return toEmit;
}

template <class CellType>
bool BoardGame<CellType>::addPlayer(std::string playerName){
    players.push_back(playerName);
    return true;
}

template <class CellType>
bool BoardGame<CellType>::startGame(){
    gameStatus.isGameStarted = true;
    gameStatus.isGameEnded = false;
    return true;
}

template <class CellType>
bool BoardGame<CellType>::endGame(){
    gameStatus.isGameStarted = false;
    gameStatus.isGameEnded = true;
    return true;
}

template <class CellType>
SGameStatus BoardGame<CellType>::getGameStatus(){
    return this->gameStatus;
}




