// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection -fsanitize=undefined" }
// -fsanitize=undefined implies -fno-delete-null-pointer-checks.  A pointer
// from define_static_string is still not null in a constant expression, so
// string_view::find on it, which checks char_traits::find's result against
// null, is a constant expression.

#include <meta>
#include <span>
#include <string_view>
#include <vector>

constexpr const char *p = std::define_static_string ("abc");
static_assert (p != nullptr);

constexpr std::string_view s = std::define_static_string ("hello world");
static_assert (s.find ("world") == 6);
static_assert (s.find ('o') == 4);
static_assert (s.find ("nope") == std::string_view::npos);

constexpr std::span<const int> a = std::define_static_array (std::vector<int>{1, 2, 3});
static_assert (a.data () != nullptr);
