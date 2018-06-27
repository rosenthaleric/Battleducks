#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "duckfamily.h"
#include "boardview.h"
//#include "setupview.h"    TODO

class Game
{
public:
    Game();

    bool setFamily(Board*);                   // TODO: board-method, telling if there are families left to set
    //void updateSetupView(SetupView*);
    void setupCPU();
    int setGamePhase(int phase);

    void progress();
    int changeTurn();
    bool shootTile(Board* board, int index);  // bool to determine success and consecutive turn
    void updateView(BoardView*);

    bool hasLost();
    void showGameOver();

private:
    Board* player_board_;
    Board* cpu_board_;
    BoardView* player_view_;
    BoardView* cpu_view_;
    int game_phase_;
    // CPU cpu_enemy;
    // SetupView setup_view_;
}

#endif // GAME_H
