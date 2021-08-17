#ifndef KOMA_HPP
#define KOMA_HPP

#include <variant>
#include <cassert>
#include <optional>

struct 先手 {};
struct 後手 {};
struct 先歩 { constexpr bool operator==(const 先歩&) { return true; } };
struct 先と { constexpr bool operator==(const 先と&) { return true; } };
struct 先王 { constexpr bool operator==(const 先王&) { return true; } };
struct 先金 { constexpr bool operator==(const 先金&) { return true; } };
struct 先銀 { constexpr bool operator==(const 先銀&) { return true; } };
struct 先成銀 { constexpr bool operator==(const 先成銀&) { return true; } };
struct 後歩 { constexpr bool operator==(const 後歩&) { return true; } };
struct 後と { constexpr bool operator==(const 後と&) { return true; } };
struct 後王 { constexpr bool operator==(const 後王&) { return true; } };
struct 後金 { constexpr bool operator==(const 後金&) { return true; } };
struct 後銀 { constexpr bool operator==(const 後銀&) { return true; } };
struct 後成銀 { constexpr bool operator==(const 後成銀&) { return true; } };

using 駒_t = std::variant<先歩, 先と, 先王, 先金, 先銀, 先成銀, 後歩, 後と, 後王, 後金, 後銀, 後成銀>;

constexpr int test_quie9b() {
    using std::holds_alternative;

    {
        const std::array<駒_t, 5> ar{先歩{}, 先銀{}, 後と{}, 後金{}, 後成銀{}};
        assert(holds_alternative<先歩>(ar[0]));
        assert(holds_alternative<先銀>(ar[1]));
        assert(holds_alternative<後と>(ar[2]));
        assert(holds_alternative<後金>(ar[3]));
        assert(holds_alternative<後成銀>(ar[4]));
    }

    {
        assert(先歩{} == 先歩{});
    }

    {
        using std::nullopt;
        const std::array<std::optional<駒_t>, 5> ar{nullopt, 先と{}, 先銀{}, nullopt, 後歩{}};
        assert(!ar[0]);
        assert(holds_alternative<先と>(ar[1].value()));
        assert(holds_alternative<先銀>(ar[2].value()));
        assert(!ar[3]);
        assert(holds_alternative<後歩>(ar[4].value()));
    }

    return 0;
}

template<int N> struct test_jf83q2 {};

constexpr auto you_dont_refer_to_me = test_jf83q2<test_quie9b()>{};

#endif