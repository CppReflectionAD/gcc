// cpp_reflection_ad#278: the scope of a switch that declares a variable
// reaches an importer of the body as the switch statement.

#include <meta>
#include <string>

using namespace std::meta;

inline int
cond_decl (int x)
{
  switch (int y = x + 1)
    {
    case 2:
      x = y;
      break;
    default:
      x = 3;
    }
  return x;
}

inline int
destroyed (int x)
{
  switch (std::string s = "ab"; x)
    {
    case 1:
      x = s.size ();
      break;
    default:
      x = 4;
    }
  return x;
}

template <typename T> T
in_template (T x)
{
  switch (T y = x; y)
    {
    case 2:
      x = y + 1;
      break;
    default:
      x = 5;
    }
  return x;
}

// FN's body is a switch of N parts, the first of which declares a variable,
// and a return.
consteval bool
switch_with (info fn, std::size_t n)
{
  auto body = statements_of (body_of (fn));
  if (body.size () != 2 || !is_return_statement (body[1]))
    return false;
  info s = body[0];
  if (!is_statement (s) || is_compound_statement (s))
    return false;
  auto parts = statements_of (s);
  return (parts.size () == n
	  && is_declaration_statement (parts[0])
	  && !is_declaration_statement (parts[1])
	  && is_compound_statement (parts[n - 1])
	  && s == body[0]);
}
