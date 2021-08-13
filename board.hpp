#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>

#include "koma.hpp"
#include "log.hpp"

// クラス

struct Location {
    int X;
    int Y;
};

class Te {
   public:
    Location cur;
    Location dest;
    Koma koma;
    void showTe();
};

class Board {
    Koma koma[6][5];
    std::vector<Koma> senteMotigoma;
    std::vector<Koma> goteMotigoma;
    int player = 1;

   public:
    void initialize();
    void print();
    void move(Te te);
    bool verifyMove(Te te);
    void setPlayer(int n);
    void changePlayer();
    int getPlayer();
    bool inputMoveFromCUI();
    void inputMoveFromCUIUsingList();
    bool isAbleToPromote(Location cur, Location dest);
    int isEnded();  // 0:終わっていない 1:先手の勝ち -1:後手の勝ち
    std::vector<Te> getVerifiedMoves();

    Log log;
};
#endif  // BOARD_HPP