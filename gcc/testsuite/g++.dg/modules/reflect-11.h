// cpp_reflection_ad#270: an `if` with no `else` reaches an importer of the
// body with no else part.

#include <meta>

using namespace std::meta;

inline int
no_else (int x)
{
  if (x)
    x = x + 1;
  return x;
}

template <typename T> T
tno_else (T x)
{
  if (x)
    x = x + 1;
  return x;
}

consteval bool
if_parts (info fn, std::size_t n)
{
  return statements_of (statements_of (body_of (fn))[0]).size () == n;
}
