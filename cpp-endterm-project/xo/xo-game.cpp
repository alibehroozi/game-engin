
#include "xo-game.h"

XOGame::XOGame(int socketClient):BoardGame(3,3,2,socketClient){}

void XOGame::configure(){
   
}

void XOGame::checkGameEnded(){
    bool isCellNull = false;
    bool isGameEnded = false;
    char winner = 0;
    int winnerIndex = -1;
    for(int i = 0;i<9;i++){
        if(getCells()[i].getValue() == 0)
            isCellNull = true;
    }
    if(getCells()[0].getValue() == getCells()[4].getValue() && getCells()[4].getValue() == getCells()[8].getValue()){
        winner = getCells()[0].getValue();
    }
    if(getCells()[2].getValue() == getCells()[4].getValue() && getCells()[4].getValue() == getCells()[6].getValue()){
        winner = getCells()[2].getValue();
    }
    if(getCells()[1].getValue() == getCells()[4].getValue() && getCells()[4].getValue() == getCells()[7].getValue()){
        winner = getCells()[1].getValue();
    }
    if(getCells()[3].getValue() == getCells()[4].getValue() && getCells()[4].getValue() == getCells()[5].getValue()){
        winner = getCells()[3].getValue();
    }
    if(getCells()[0].getValue() == getCells()[1].getValue() && getCells()[1].getValue() == getCells()[2].getValue()){
        winner = getCells()[0].getValue();
    }
    if(getCells()[6].getValue() == getCells()[7].getValue() && getCells()[7].getValue() == getCells()[8].getValue()){
        winner = getCells()[6].getValue();
    }
    if(getCells()[0].getValue() == getCells()[3].getValue() && getCells()[3].getValue() == getCells()[6].getValue()){
        winner = getCells()[0].getValue();
    }
    if(getCells()[2].getValue() == getCells()[5].getValue() && getCells()[5].getValue() == getCells()[8].getValue()){
        winner = getCells()[2].getValue();
    }
    if(winner == 'x'){
        winnerIndex = 0;
        isGameEnded = true;
    }
    if(winner == 'o'){
        winnerIndex = 1;
        isGameEnded = true;
    }
    if(isCellNull == false && winner == 0){
        isGameEnded = true;
        winnerIndex = -1;
    }
    gameStatus.isGameEnded = isGameEnded;
    gameStatus.winner = winnerIndex;
}
