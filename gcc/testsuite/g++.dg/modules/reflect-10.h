// cpp_reflection_ad#268: a plain `if` with a constant condition reaches an
// importer of the body as one statement.

#include <meta>

using namespace std::meta;

inline int
if_true (int x)
{
  if (true)
    x = x + 1;
  return x;
}

template <typename T> T
tif_sizeof (T x)
{
  if (sizeof (T) >= 2)
    x = x + 1;
  else
    (void) x;
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
