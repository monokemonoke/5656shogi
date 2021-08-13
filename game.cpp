#include "game.hpp"

#include <assert.h>

#include <iostream>
#include <random>
#include <stack>
#include <vector>

#include "board.hpp"
#include "log.hpp"

Game::Game() {
    Game::log.displayLevel = LOG_DEBUG;
    Game::log.displayTime = false;

    Game::init();
}

void Game::inputFromCUI() { board.inputMoveFromCUIUsingList(); }

void Game::init() { board.initialize(); }

void Game::inputFromRandom() {
    std::vector<Te> Moves;
    std::random_device rand;
    Te te;
    Moves = Game::board.getVerifiedMoves();
    assert(Moves.size() > 0);
    int choice = (int)rand() % Moves.size();
    assert(choice >= 0 && choice < Moves.size());
    te = Moves[choice];
    board.move(te);
    te.showTe();
}

void Game::showVerifiedMoves() {
    int i = 0;
    for (auto &te : Game::board.getVerifiedMoves()) {
        printf("%2d| ", ++i);
        te.showTe();
    }
}

void Game::play() {
    Game::init();
    while (true) {
        board.print();
        if (board.getPlayer() > 0) {
            Game::inputFromCUI();
        } else {
            Game::inputFromRandom();
        }
        if (board.isEnded() != 0) break;
        board.changePlayer();
    }
    if (board.isEnded() > 0) {
        puts("INFO 先手の勝ち");
    } else {
        puts("INFO 後手の勝ち");
    }
    board.print();
    puts("INFO the program was ended.");
}

void Game::searchDeep(Board board, int *gameCases,
                      std::vector<Te> *chosenMoves) {
    std::vector<Te> Moves = board.getVerifiedMoves();
    assert(Moves.size() > 0);

    // for文の中で
    // 前の手を削除する->次の手を追加する
    // の流れで書けるよう、最初に仮の手を追加しておく
    Te tempTe;
    chosenMoves->push_back(tempTe);

    for (Te move : Moves) {
        Board tmpBoard = board;
        tmpBoard.move(move);
        tmpBoard.changePlayer();

        chosenMoves->pop_back();
        chosenMoves->push_back(move);

        if (tmpBoard.isEnded() == 0) {
            // 千日手みたいな局面になった場合、
            // 4096手以降を基準に調査を一旦終える
            if (chosenMoves->size() > 256) return;

            Game::searchDeep(tmpBoard, gameCases, chosenMoves);
        } else {
            *gameCases += 1;

            // for (Te te : *chosenMoves) te.showTe();
            log.info("%sの勝ち", (tmpBoard.isEnded() > 0) ? "先手" : "後手");
            log.info("gameCases = %d", *gameCases);
            // tmpBoard.print();
            log.info("INFO終了");

            // if (*gameCases > 1024) exit(EXIT_SUCCESS);
        }
    }
    log.info("Now gameCases = %d", *gameCases);
}

void Game::searchAll() {
    int gameCases = 0;
    std::vector<Te> chosenMoves;
    std::stack<int> chosenMoveIndex;

    log.info("Game::searchAll searching start");

    Board board;
    board.initialize();
    Game::searchDeep(board, &gameCases, &chosenMoves);

    log.info("Game::searchAll searching finish");
}

void Game::playCPUvsCPU() {
    int limit;
    int firstWin = 0, secondWin = 0;
    std::cin >> limit;
    for (int i = 1; i <= limit; i++) {
        printf("INFO %2d回目のゲーム\n", i);
        Game::init();
        while (true) {
            board.print();
            Game::inputFromRandom();

            if (board.isEnded() != 0) break;
            board.changePlayer();
        }
        if (board.isEnded() > 0) {
            puts("INFO 先手の勝ち");
            firstWin++;
        } else {
            puts("INFO 後手の勝ち");
            secondWin++;
        }
        board.print();
    }
    printf("INFO %2dゲーム中 先手%2d 後手%2d\n", limit, firstWin, secondWin);
    puts("INFO the program was ended.");
}
// EOF