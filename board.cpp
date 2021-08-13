#include "board.hpp"

#include <stdio.h>

#include <iostream>
#include <vector>

#include "log.hpp"

// 定数
const Location MOVE_N = {0, -1};
const Location MOVE_NE = {1, -1};
const Location MOVE_NW = {-1, -1};
const Location MOVE_E = {1, 0};
const Location MOVE_W = {-1, 0};
const Location MOVE_S = {0, 1};
const Location MOVE_SE = {1, 1};
const Location MOVE_SW = {-1, 1};
const Location MOVE_EMPTY = {0, 0};

const Location MOVE_OU[8] = {
    MOVE_N, MOVE_NE, MOVE_NW, MOVE_E, MOVE_W, MOVE_S, MOVE_SE, MOVE_SW,
};
const Location MOVE_KI[8] = {
    MOVE_N, MOVE_NE, MOVE_NW, MOVE_E, MOVE_W, MOVE_S, MOVE_EMPTY, MOVE_EMPTY,
};
const Location MOVE_GI[8] = {
    MOVE_N,     MOVE_NE,    MOVE_NW, MOVE_EMPTY,
    MOVE_EMPTY, MOVE_EMPTY, MOVE_SE, MOVE_SW,
};
const Location MOVE_FU[8] = {
    MOVE_N,     MOVE_EMPTY, MOVE_EMPTY, MOVE_EMPTY,
    MOVE_EMPTY, MOVE_EMPTY, MOVE_EMPTY, MOVE_EMPTY,
};
const Location MOVE_NG[8] = {
    MOVE_N, MOVE_NE, MOVE_NW, MOVE_E, MOVE_W, MOVE_S, MOVE_EMPTY, MOVE_EMPTY,
};
const Location MOVE_TO[8] = {
    MOVE_N, MOVE_NE, MOVE_NW, MOVE_E, MOVE_W, MOVE_S, MOVE_EMPTY, MOVE_EMPTY,
};
const Location MOVE_EMPTYS[8] = {
    MOVE_EMPTY, MOVE_EMPTY, MOVE_EMPTY, MOVE_EMPTY,
    MOVE_EMPTY, MOVE_EMPTY, MOVE_EMPTY, MOVE_EMPTY,
};

const Location* MOVE_DIRECTIONS[7] = {
    MOVE_EMPTYS, MOVE_OU, MOVE_KI, MOVE_GI, MOVE_NG, MOVE_FU, MOVE_TO,
};

void Board::initialize() {
    Board::log.displayLevel = LOG_INFO;
    Board::log.displayTime = false;

    Board::setPlayer(1);
    Board::senteMotigoma.clear();
    Board::goteMotigoma.clear();

    for (int y = 0; y < 6; y++) {
        for (int x = 0; x < 5; x++) {
            Board::koma[y][x].setKind(0);
        }
    }

    Board::koma[0][0].setKind(-3);
    Board::koma[0][1].setKind(-2);
    Board::koma[0][2].setKind(-1);
    Board::koma[0][3].setKind(-2);
    Board::koma[0][4].setKind(-3);

    Board::koma[2][1].setKind(-5);
    Board::koma[2][2].setKind(-5);
    Board::koma[2][3].setKind(-5);

    Board::koma[3][1].setKind(5);
    Board::koma[3][2].setKind(5);
    Board::koma[3][3].setKind(5);

    Board::koma[5][0].setKind(3);
    Board::koma[5][1].setKind(2);
    Board::koma[5][2].setKind(1);
    Board::koma[5][3].setKind(2);
    Board::koma[5][4].setKind(3);
}

void Board::print() {
    puts("後手:");
    for (auto& e : Board::goteMotigoma) {
        printf(" %s", e.getChar());
    }
    puts("");

    puts("   |  1|  2|  3|  4|  5|");
    puts("---+---+---+---+---+---+");
    for (int y = 0; y < 6; y++) {
        printf("P %d|", y + 1);
        for (int x = 0; x < 5; x++) {
            printf("%s|", Board::koma[y][x].getChar());
        }
        puts("");
        puts("---+---+---+---+---+---+");
    }

    puts("先手:");
    for (auto& e : Board::senteMotigoma) {
        printf(" %s", e.getChar());
    }
    puts("");
}

void Board::move(Te te) {
    te.dest.Y--;
    te.dest.X--;

    log.debug("Board::move move()が呼ばれました！！");
    log.debug("Board::move cur{%2d %2d}", te.cur.X, te.cur.Y);

    if (te.cur.X == 0 && te.cur.Y == 0) {
        // 持ち駒を打つ場合
        log.debug("Board::move 持ち駒が打たれています.");
        Board::koma[te.dest.Y][te.dest.X] = te.koma;
        // 持ち駒から削除
        bool debugFlag = true;
        if (te.koma.getKind() > 0) {
            log.debug("Board::move 先手の持駒");
            for (int i = 0; i < senteMotigoma.size(); i++) {
                if (senteMotigoma[i].getKind() == te.koma.getKind()) {
                    log.debug("Board::move motiogma[%2d]%sを消します.", i,
                              senteMotigoma[i].getChar());
                    senteMotigoma[i] = senteMotigoma.back();
                    senteMotigoma.pop_back();
                    debugFlag = false;
                    break;
                }
            }
        } else {
            log.debug("Board::move 後手の持駒");
            for (int i = 0; i < goteMotigoma.size(); i++) {
                if (goteMotigoma[i].getKind() == te.koma.getKind()) {
                    log.debug("Board::move motiogma[%2d]%sを消します.", i,
                              goteMotigoma[i].getChar());
                    goteMotigoma[i] = goteMotigoma.back();
                    goteMotigoma.pop_back();
                    debugFlag = false;
                    break;
                }
            }
        }
        if (debugFlag) log.error("Board::move 持ち駒が削除されませんでした");
    } else {
        te.cur.Y--;
        te.cur.X--;
        // 盤上の駒を動かす場合
        if (Board::koma[te.dest.Y][te.dest.X].getKind() != 0) {
            // 移動先に駒があった場合の対応
            Koma temp;
            temp = Board::koma[te.dest.Y][te.dest.X];
            temp.setKind(temp.getKind() * -1);
            if (temp.isPromoted()) temp.getDemoted();
            if (Board::koma[te.dest.Y][te.dest.X].getKind() > 0) {
                Board::goteMotigoma.push_back(temp);
            } else {
                Board::senteMotigoma.push_back(temp);
            }
        }
        Board::koma[te.dest.Y][te.dest.X] = te.koma;
        Board::koma[te.cur.Y][te.cur.X].setKind(0);
    }
}

bool Board::verifyMove(Te te) {
    // teのX,Yの値が正しい値域に存在しているか確認する
    if (te.cur.X < 0 || te.cur.X > 5) {
        log.debug("Board::verifyMove | 不正な値域 curX = %d", te.cur.X);
        return false;
    }
    if (te.cur.Y < 0 || te.cur.Y > 6) {
        log.debug("Board::verifyMove | 不正な値域 curY = %d", te.cur.Y);
        return false;
    }
    if (te.dest.X < 1 || te.dest.X > 5) {
        log.debug("Board::verifyMove | 不正な値域 destX = %d", te.dest.X);
        return false;
    }
    if (te.dest.Y < 1 || te.dest.Y > 6) {
        log.debug("Board::verifyMove | 不正な値域 destY = %d", te.dest.Y);
        return false;
    }

    int curKomaKind;
    if (te.cur.X != 0 && te.cur.Y != 0) {
        curKomaKind = Board::koma[te.cur.Y - 1][te.cur.X - 1].getKind();
    } else {
        curKomaKind = te.koma.getKind();
    }
    int destKomaKind = Board::koma[te.dest.Y - 1][te.dest.X - 1].getKind();

    if (curKomaKind * Board::player <= 0) {
        log.warn("Board::verifyMove | 動かす駒が存在しません");
        log.warn(
            "Board::verifyMove | curKomaKind × player = %+d × %+d = "
            "%+d",
            curKomaKind, player, curKomaKind * player);
        return false;
    }
    if (curKomaKind * destKomaKind > 0) {
        log.debug("Board::verifyMove | 移動先に自駒が存在します");
        log.debug("Board::verifyMove | curKind = %+d destKind = %+d",
                  curKomaKind, destKomaKind);
        return false;
    }

    // 打つ駒が持ち駒からか盤上からかで場合分け
    if (te.cur.X != 0 && te.cur.Y != 0) {
        //  盤上の場合
        struct Location diff;
        diff.X = te.dest.X - te.cur.X;
        diff.Y = te.dest.Y - te.cur.Y;

        int changeDirectionByPlayer = (curKomaKind > 0) ? 1 : -1;

        bool isExistDirection = false;
        for (int i = 0; i < 8; i++) {
            bool checkX = (diff.X == MOVE_DIRECTIONS[abs(curKomaKind)][i].X *
                                         changeDirectionByPlayer);
            bool checkY = (diff.Y == MOVE_DIRECTIONS[abs(curKomaKind)][i].Y *
                                         changeDirectionByPlayer);
            if (checkX && checkY) {
                isExistDirection = true;
                break;
            }
        }
        if (!isExistDirection) {
            log.debug("Board::verifyMove | 移動先にその駒は動けません.");
            return false;
        }
    } else {
        // 持ち駒の場合
        if (destKomaKind != 0) return false;
        bool isExistFlag = false;
        if (Board::player > 0) {
            for (auto& koma : senteMotigoma) {
                if (koma.getKind() != te.koma.getKind()) continue;
                isExistFlag = true;
                break;
            }
        } else {
            for (auto& koma : goteMotigoma) {
                if (koma.getKind() != te.koma.getKind()) continue;
                isExistFlag = true;
                break;
            }
        }
        if (!isExistFlag) {
            log.warn("Board::verifyMove | 持ち駒にその駒は存在しません");
            return false;
        }
    }

    // すべてのチェックを通り抜けれたのなら
    // そのMoveは合法手である.
    return true;
}

void Board::setPlayer(int n) {
    if (n == -1 || n == 1) {
        Board::player = n;
    } else {
        log.warn("Board::setPlayer | 不正な引数n = %d", n);
    }
}

void Board::changePlayer() {
    (Board::player > 0) ? Board::setPlayer(-1) : Board::setPlayer(1);
}

int Board::getPlayer() { return Board::player; }

bool Board::inputMoveFromCUI() {
    Te testTe;
    std::cin >> testTe.cur.X >> testTe.cur.Y >> testTe.dest.X >> testTe.dest.Y;
    if (testTe.cur.X != 0 && testTe.cur.Y != 0) {
        testTe.koma = Board::koma[testTe.cur.Y - 1][testTe.cur.X - 1];
        if (Board::isAbleToPromote(testTe.cur, testTe.dest)) {
            puts("成りますか？ (y/n)");
            char buff;
            std::cin >> buff;
            if (buff == 'y') testTe.koma.getPromoted();
        }
    } else {
        puts("1:OU 2:KN 3:GI 4:NG 5:FU 6:TO");
        int n;
        std::cin >> n;
        testTe.koma.setKind(n);
    }
    if (Board::verifyMove(testTe)) {
        Board::move(testTe);
        return true;
    } else {
        puts("その手は有効ではありません。もう一度お確かめください.");
        return false;
    }
}

void Board::inputMoveFromCUIUsingList() {
    Te te;
    std::vector<Te> Moves;
    Moves = Board::getVerifiedMoves();
    int n;
    while (true) {
        int i = 0;
        for (auto move : Moves) {
            printf("%2d | ", ++i);
            move.showTe();
        }
        std::cin >> n;
        if (n >= 1 && n <= Moves.size()) break;
    }
    n--;
    te = Moves[n];
    Board::move(te);
    printf("%2d | ", n);
    te.showTe();
}

bool Board::isAbleToPromote(Location cur, Location dest) {
    if (cur.X == 0 || cur.Y == 0) return false;
    if (!Board::koma[cur.Y - 1][cur.X - 1].isAbleToPromote()) return false;
    if (Board::koma[cur.Y - 1][cur.X - 1].getKind() > 0) {
        if (dest.Y >= 3) return false;
    } else {
        if (dest.Y <= 4) return false;
    }
    return true;
}

int Board::isEnded() {
    bool senteF = false;
    bool goteF = false;
    for (auto item : senteMotigoma) {
        if (item.getKind() == 1) {
            senteF = true;
            break;
        }
    }
    for (auto item : goteMotigoma) {
        if (item.getKind() == -1) {
            goteF = true;
            break;
        }
    }
    if (senteF && goteF) {
        log.error("Board::isEnded | 先手後手ともに王が持ち駒にあります.\n");
        return 0;
    }
    if (senteF) return 1;
    if (goteF) return -1;
    return 0;
}

std::vector<Te> Board::getVerifiedMoves() {
    log.debug("Board::getVerifiedMoveが呼び出されました");
    log.debug("player %d", Board::player);

    std::vector<Te> verifiedMoves;
    std::vector<Location> emptyPlaces;
    std::vector<Location> alliesPlaces;

    for (int y = 0; y < 6; y++) {
        for (int x = 0; x < 5; x++) {
            if (Board::koma[y][x].getKind() == 0) {
                emptyPlaces.push_back(Location{x, y});
            } else if (Board::koma[y][x].getKind() * Board::player > 0) {
                alliesPlaces.push_back(Location{x, y});
            }
        }
    }
    log.debug("Board::getVerifiedMove 味方・空白の場所を確認し終わりました.");
    log.debug("empty_places : %lu", emptyPlaces.size());
    log.debug("alliesPlaces : %lu", alliesPlaces.size());

    // debug用
    for (auto e : emptyPlaces) {
        log.debug("empty_places { %d %d }", e.X, e.Y);
    }

    for (auto& location : alliesPlaces) {
        Te move;
        move.cur = location;
        const int kind = Board::koma[location.Y][location.X].getKind();
        for (int i = 0; i < 8; i++) {
            Location direction = MOVE_DIRECTIONS[abs(kind)][i];
            direction.X *= Board::player;
            direction.Y *= Board::player;
            move.dest.X = direction.X + location.X;
            move.dest.Y = direction.Y + location.Y;
            move.koma = Board::koma[location.Y][location.X];
            Te mock = move;
            mock.cur.X++;
            mock.cur.Y++;
            mock.dest.X++;
            mock.dest.Y++;
            if (direction.X == 0 && direction.Y == 0) continue;
            if (move.dest.X < 0 || 4 < move.dest.X) continue;
            if (move.dest.Y < 0 || 5 < move.dest.Y) continue;
            if (!Board::verifyMove(mock)) continue;
            verifiedMoves.push_back(mock);
            if (move.koma.isAbleToPromote() &&
                Board::isAbleToPromote(mock.cur, mock.dest)) {
                mock.koma.getPromoted();
                verifiedMoves.push_back(mock);
            }
        }
    }
    log.debug("Board::getVerifiedMove　盤上の味方の駒の合法手を探し終えました");
    log.debug("verifiedMoves : %d", verifiedMoves.size());

    Te move;
    if (Board::player > 0) {
        for (auto koma : senteMotigoma) {
            for (auto location : emptyPlaces) {
                move.cur = Location{0, 0};
                move.dest = location;
                move.dest.X++;
                move.dest.Y++;
                move.koma = koma;
                verifiedMoves.push_back(move);
            }
        }
    } else {
        for (auto koma : goteMotigoma) {
            for (auto location : emptyPlaces) {
                move.cur = Location{0, 0};
                move.dest = location;
                move.dest.X++;
                move.dest.Y++;
                move.koma = koma;
                verifiedMoves.push_back(move);
            }
        }
    }
    log.debug("Board::getVerifiedMove　持ち駒を使った合法手を探し終えました");
    log.debug("verifiedMoves : %d", verifiedMoves.size());

    return verifiedMoves;
}

void Te::showTe() {
    printf("(%2d,%2d) To (%2d,%2d) %s\n", Te::cur.X, Te::cur.Y, Te::dest.X,
           Te::dest.Y, Te::koma.getChar());
}

// EOF