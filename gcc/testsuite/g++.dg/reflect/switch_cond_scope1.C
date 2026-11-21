// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// cpp_reflection_ad#278: the scope of a switch whose init-statement or
// condition declares a variable is the switch statement, not a compound
// statement.  Its parts are the declarations, then the condition and the
// body.

#include <meta>
#include <string>

using namespace std::meta;

int sink (int);
int sinks (const std::string &);

int
plain (int x)
{
  switch (x)
    {
    case 1:
      sink (x);
    }
  return 0;
}

int
cond_decl (int x)
{
  switch (int y = sink (x))
    {
    case 1:
      sink (y);
      break;
    default:
      break;
    }
  return 0;
}

int
init_decl (int x)
{
  switch (int y = sink (x); y)
    {
    case 1:
      sink (y);
    }
  return 0;
}

int
init_and_cond (int x)
{
  switch (int y = sink (x); int z = y)
    {
    case 1:
      sink (z);
    }
  return 0;
}

int
destroyed (int x)
{
  switch (std::string s = "a"; x)
    {
    case 1:
      sinks (s);
    }
  return 0;
}

int
nested (int x)
{
  switch (int y = x)
    {
    case 1:
      sink (y);
      switch (int z = y)
	{
	case 2:
	  sink (z);
	}
    }
  return 0;
}

template <typename T> int
in_template (T x)
{
  switch (T y = x; y)
    {
    case 1:
      sink (y);
    }
  return 0;
}

void
only (int x)
{
  switch (int y = x)
    {
    case 1:
      sink (y);
    }
}

consteval info
first (info fn)
{
  return statements_of (body_of (fn))[0];
}

// FN's body is a switch and a return.  The switch isn't a compound
// statement, and has N parts, the first D of which are declaration
// statements, and the last of which is the body.
consteval bool
switch_with (info fn, std::size_t n, std::size_t d)
{
  auto body = statements_of (body_of (fn));
  if (body.size () != 2 || !is_return_statement (body[1]))
    return false;
  info s = body[0];
  if (!is_statement (s) || is_compound_statement (s)
      || is_expression_statement (s) || is_declaration_statement (s)
      || is_if_statement (s))
    return false;
  auto parts = statements_of (s);
  if (parts.size () != n)
    return false;
  for (std::size_t i = 0; i < n; ++i)
    if (is_declaration_statement (parts[i]) != (i < d))
      return false;
  return is_compound_statement (parts[n - 1]);
}

static_assert (switch_with (^^plain, 2, 0));
static_assert (switch_with (^^cond_decl, 3, 1));
static_assert (switch_with (^^init_decl, 3, 1));
static_assert (switch_with (^^init_and_cond, 4, 2));
static_assert (switch_with (^^destroyed, 3, 1));
static_assert (switch_with (^^nested, 3, 1));
static_assert (switch_with (^^in_template<int>, 3, 1));
static_assert (switch_with (^^in_template<long>, 3, 1));

// A body that is only a switch is a block of one statement, the switch.
static_assert (is_compound_statement (body_of (^^only)));
static_assert (statements_of (body_of (^^only)).size () == 1);
static_assert (!is_compound_statement (statements_of (body_of (^^only))[0]));
static_assert (statements_of (statements_of (body_of (^^only))[0]).size ()
	       == 3);

// A switch in a switch's body is one of its statements.
consteval info
inner_switch ()
{
  info block = statements_of (first (^^nested))[2];
  for (info s : statements_of (block))
    if (is_statement (s) && !is_compound_statement (s)
	&& statements_of (s).size () == 3)
      return s;
  return info {};
}
static_assert (inner_switch () != info {});
static_assert (is_declaration_statement (statements_of (inner_switch ())[0]));
static_assert (is_compound_statement (statements_of (inner_switch ())[2]));

// The switch is equal only to itself.
static_assert (first (^^cond_decl) == first (^^cond_decl));
static_assert (first (^^cond_decl) != first (^^init_decl));
static_assert (first (^^in_template<int>) != first (^^in_template<long>));
