// cpp_reflection_ad#269: a block that is the then or else statement of an
// `if` reaches an importer of the body as a compound statement.

#include <meta>

using namespace std::meta;

inline int
then_block (int x)
{
  if (x)
    { x = x + 1; }
  else
    {}
  return x;
}

template <typename T> T
tthen_block (T x)
{
  if (x)
    { x = x + 1; }
  else
    { x = x - 1; }
  return x;
}

consteval bool
blocks (info fn, std::size_t n)
{
  auto s = statements_of (statements_of (body_of (fn))[0]);
  if (s.size () != n)
    return false;
  for (std::size_t i = 1; i < n; ++i)
    if (!is_compound_statement (s[i]))
      return false;
  return true;
}
