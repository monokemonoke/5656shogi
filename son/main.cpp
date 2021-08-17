#include <iostream>
#include <string>

#include "./matrix.hpp"
#include "./駒.hpp"
#include "./test.hpp"

using std::cout;
using std::endl;

int main() {
    using matrix_t = matrix<std::string, 3, 5>;
    const matrix_t mat{
        "あ", "い", "う", "え", "お",
        "か", "き", "く", "け", "こ",
        "さ", "し", "す", "せ", "そ",
    };
    const auto rvi = matrix_t::rvbegin(mat);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++ j) {
            cout << rvi[i][j] << " ";
        }
        cout << endl;
    }
}