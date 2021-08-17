#include "./matrix.hpp"

namespace test {

constexpr int rvi() {
    using matrix_t = matrix<int, 2, 4>;
    const matrix_t mat{
        0, 1, 2, 3,
        4, 5, 6, 7,
    };

    const auto rvi = matrix_t::rvbegin(mat);
    if (rvi[0][0] != 0) throw;
    if (rvi[0][1] != 1) throw;
    if (rvi[0][2] != 2) throw;
    if (rvi[0][3] != 3) throw;
    if (rvi[1][0] != 4) throw;
    if (rvi[1][1] != 5) throw;
    if (rvi[1][2] != 6) throw;
    if (rvi[1][3] != 7) throw;

    return 0;
}

constexpr int map() {
    using matrix_t = matrix<int, 2, 4>;
    const matrix_t mat{
        0, 1, 2, 3,
        4, 5, 6, 7,
    };

    // 各要素を2乗
    const auto mapped = matrix_t::map(mat, [](int x){ return x*x; });
    const auto rvi = matrix_t::rvbegin(mapped);
    if (rvi[0][0] != 0) throw;
    if (rvi[0][1] != 1) throw;
    if (rvi[0][2] != 4) throw;
    if (rvi[0][3] != 9) throw;
    if (rvi[1][0] != 16) throw;
    if (rvi[1][1] != 25) throw;
    if (rvi[1][2] != 36) throw;
    if (rvi[1][3] != 49) throw;

    return 0;
}

constexpr int map_with_idx() {
    using matrix_t = matrix<int, 2, 4>;
    const matrix_t mat{
        0, 1, 2, 3,
        4, 5, 6, 7,
    };

    // 添字と要素を足す
    const auto mapped_with_idx = matrix_t::map_with_idx(mat, [](int i, int x){ return i+x; });
    const auto rvi = matrix_t::rvbegin(mapped_with_idx);
    if (rvi[0][0] != 0) throw;
    if (rvi[0][1] != 2) throw;
    if (rvi[0][2] != 4) throw;
    if (rvi[0][3] != 6) throw;
    if (rvi[1][0] != 8) throw;
    if (rvi[1][1] != 10) throw;
    if (rvi[1][2] != 12) throw;
    if (rvi[1][3] != 14) throw;

    return 0;
}

constexpr int update_at() {
    using matrix_t = matrix<int, 2, 4>;
    const matrix_t mat{
        0, 1, 2, 3,
        4, 5, 6, 7,
    };

    // 添字3だけ42に変更
    const auto updated = matrix_t::update_at(mat, 3, [](int _){ return 42; });
    const auto rvi = matrix_t::rvbegin(updated);
    if (rvi[0][0] != 0) throw;
    if (rvi[0][1] != 1) throw;
    if (rvi[0][2] != 2) throw;
    if (rvi[0][3] != 42) throw;
    if (rvi[1][0] != 4) throw;
    if (rvi[1][1] != 5) throw;
    if (rvi[1][2] != 6) throw;
    if (rvi[1][3] != 7) throw;

    return 0;
}

template<int N> struct test {};
auto you_dont_refer_to_me = test<rvi() + map() + map_with_idx() + update_at()>{};

}