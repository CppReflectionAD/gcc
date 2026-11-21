// cpp_reflection_ad#278: the scope of an if that declares a variable reaches
// an importer of the body as the if statement.

#include <meta>
#include <string>

using namespace std::meta;

inline int
cond_decl (int x)
{
  if (int y = x + 1)
    x = y;
  else
    x = 2;
  return x;
}

inline int
destroyed (int x)
{
  if (std::string s = "ab"; x)
    x = s.size ();
  else
    x = 3;
  return x;
}

template <typename T> T
in_template (T x)
{
  if (T y = x; y > 1)
    x = y + 1;
  else
    x = 4;
  return x;
}

// FN's body is an if of N parts, the first of which declares a variable, and
// a return.
consteval bool
if_with (info fn, std::size_t n)
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
	  && is_expression (condition_of (s))
	  && s == body[0]);
}
