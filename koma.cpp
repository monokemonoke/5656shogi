#include "koma.hpp"

#include <iostream>

#include "log.hpp"

// グローバル定数
const int DEBUG = 1;

Koma::Koma() { Koma::kind = 0; }

void Koma::setKind(int n) {
    if (n < -6 || 6 < n) {
        if (DEBUG > 0)
            printf("ERROR class'Koma'::setKind invalid argument n : n = %d", n);
        n = 0;
    }
    Koma::kind = n;
}

int Koma::getKind() { return Koma::kind; }

const char* Koma::getChar() {
    switch (Koma::kind) {
        case 0:
            return " * ";
            break;
        case 1:
            return "+OU";
            break;
        case 2:
            return "+KI";
            break;
        case 3:
            return "+GI";
            break;
        case 4:
            return "+NG";
            break;
        case 5:
            return "+FU";
            break;
        case 6:
            return "+TO";
            break;
        case -1:
            return "-OU";
            break;
        case -2:
            return "-KI";
            break;
        case -3:
            return "-GI";
            break;
        case -4:
            return "-NG";
            break;
        case -5:
            return "-FU";
            break;
        case -6:
            return "-TO";
            break;
        default:
            if (DEBUG > 0)
                printf(
                    "ERROR class'Koma'::getChar invalid value Koma::kind = "
                    "%d\n",
                    Koma::kind);
            return " * ";
            break;
    }
}

void Koma::getPromoted() {
    switch (Koma::kind) {
        case 3:
        case 5:
            Koma::kind++;
            break;
        case -3:
        case -5:
            Koma::kind--;
            break;
    }
}

void Koma::getDemoted() {
    switch (Koma::kind) {
        case 4:
        case 6:
            Koma::kind--;
            break;
        case -4:
        case -6:
            Koma::kind++;
            break;
    }
}

bool Koma::isAbleToPromote() {
    switch (Koma::kind) {
        case 3:
        case 5:
        case -3:
        case -5:
            return true;
            break;
        default:
            return false;
    }
}

bool Koma::isPromoted() {
    switch (Koma::kind) {
        case 4:
        case 6:
        case -4:
        case -6:
            return true;
            break;
        default:
            return false;
            break;
    }
}