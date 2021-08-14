#include <iostream>
#include <array>

template<typename ElemT, int M, int N> struct matrix : std::array<ElemT, M*N> {
    using matrix_t = matrix<ElemT, M, N>;

    struct row_vec_iter {
        struct col_iter {
            const row_vec_iter rvi;
            const int n;
            constexpr col_iter(const row_vec_iter _row_vec_iter, int offset = 0)
                : rvi{_row_vec_iter}, n{offset} {}
            constexpr const ElemT& operator*() const { return rvi.mat[rvi.m*N + n]; }
            constexpr const ElemT& operator[](int d) const { return rvi.mat[rvi.m*N + n+d]; }
        };

        const matrix_t& mat;
        const int m;
        constexpr row_vec_iter(const matrix_t& _mat, int offset = 0) : mat{_mat}, m{offset} {}
        constexpr const col_iter operator*() const { return col_iter{*this, m}; }
        constexpr const col_iter operator[](int d) const { return col_iter{row_vec_iter{mat, m+d}}; }
    };

    /* statics */
    constexpr static row_vec_iter rvbegin(const matrix& mat) { return row_vec_iter{mat, 0}; }
    template<typename UnaryOperation>
    constexpr static matrix_t map(const matrix& mat, UnaryOperation op) {
        matrix out{};
        for (int i = 0; i < M*N; ++i) out[i] = op(mat[i]);
        return out;
    }
    template<typename BinaryOperation>
    constexpr static matrix_t map_with_idx(const matrix& mat, BinaryOperation op) {
        matrix out{};
        for (int i = 0; i < M*N; ++i) out[i] = op(i, mat[i]);
        return out;
    }
    template<typename UnaryOperation>
    constexpr static matrix_t update_at(const matrix& mat, int where, UnaryOperation op) {
        return map_with_idx(mat, [=](int i, int x){ return i == where ? op(mat[i]) : mat[i]; });
    }
};
