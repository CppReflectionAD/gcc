// cpp_reflection_ad#250: an `if constexpr` reaches an importer of the body as
// one statement.

#include <meta>

using namespace std::meta;

inline int
if_constexpr (int x)
{
  if constexpr (sizeof (int) >= 2)
    x = x + 1;
  return x;
}

template <typename T> T
tif_constexpr (T x)
{
  if constexpr (sizeof (T) >= 2)
    x = x + 1;
  return x;
}

consteval bool
if_first (info fn)
{
  auto s = statements_of (body_of (fn));
  return (s.size () == 2
	  && is_statement (s[0])
	  && !is_expression_statement (s[0])
	  && !is_compound_statement (s[0])
	  && is_return_statement (s[1]));
}
