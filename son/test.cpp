#include "./test.hpp"

int main() {
    test::test<test::rvi()>{};
    test::test<test::map()>{};
    test::test<test::map_with_idx()>{};
    test::test<test::update_at()>{};

    std::cout << "テスト成功" << std::endl;
    return 0;
}