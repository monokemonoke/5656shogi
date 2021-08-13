#ifndef GAME_HPP
#define GAME_HPP

#include <stack>
#include <vector>

#include "board.hpp"
#include "log.hpp"

class Game {
    Board board;

   public:
    Game();
    void init();
    void inputFromCUI();
    void inputFromRandom();
    void showVerifiedMoves();
    void play();
    void playCPUvsCPU();
    void searchAll();
    void searchDeep(Board board, int *gameCases, std::vector<Te> *chosenMoves);
    Log log;
};

#endif  // GAME_HPP