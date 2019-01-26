
#ifndef xo_game_h
#define xo_game_h

#include "../engin/board-game.cpp"


class XOGame:public BoardGame<char>{
public:
    XOGame(int socketClient);
    void configure();
    void checkGameEnded();
};


#endif

