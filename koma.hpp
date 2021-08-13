#ifndef KOMA_HPP
#define KOMA_HPP

class Koma {
    int kind;

   public:
    Koma();
    void setKind(int n);
    int getKind();
    const char* getChar();
    void getPromoted();
    void getDemoted();
    bool isAbleToPromote();
    bool isPromoted();
};

#endif  // KOMA_HPP