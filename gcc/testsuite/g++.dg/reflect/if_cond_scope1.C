// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// cpp_reflection_ad#278: the scope of an if whose init-statement or condition
// declares a variable is the if statement, not a compound statement.  Its
// parts are the declarations, then the condition and the clauses.

#include <meta>
#include <string>

using namespace std::meta;

int sink (int);
int sinks (const std::string &);

int
cond_decl (int x)
{
  if (int y = sink (x))
    sink (y);
  else
    sink (1);
  return 0;
}

int
init_decl (int x)
{
  if (int y = sink (x); y > 1)
    sink (y);
  else
    sink (1);
  return 0;
}

int
init_and_cond (int x)
{
  if (int y = sink (x); int z = y)
    sink (z);
  else
    sink (1);
  return 0;
}

int
destroyed (int x)
{
  if (std::string s = "a"; x)
    sinks (s);
  else
    sink (1);
  return 0;
}

int
block_decl (int x)
{
  if (x)
    {
      int y = x;
      sink (y);
    }
  else
    sink (1);
  return 0;
}

int
nested (int x)
{
  if (int y = x)
    {
      sink (y);
      if (int z = y)
	sink (z);
      else
	sink (2);
    }
  else
    sink (1);
  return 0;
}

template <typename T> int
in_template (T x)
{
  if (T y = x; y)
    sink (y);
  else
    sink (1);
  return 0;
}

consteval info
first (info fn)
{
  return statements_of (body_of (fn))[0];
}

// FN's body is an if and a return.  The if isn't a compound statement, and
// has N parts, the first D of which are declaration statements.
consteval bool
if_with (info fn, std::size_t n, std::size_t d)
{
  auto body = statements_of (body_of (fn));
  if (body.size () != 2 || !is_return_statement (body[1]))
    return false;
  info s = body[0];
  if (!is_statement (s) || is_compound_statement (s)
      || is_expression_statement (s) || is_declaration_statement (s))
    return false;
  auto parts = statements_of (s);
  if (parts.size () != n)
    return false;
  for (std::size_t i = 0; i < n; ++i)
    if (is_declaration_statement (parts[i]) != (i < d))
      return false;
  return is_expression (condition_of (s))
	 && is_statement (true_expression_of (s))
	 && is_statement (false_expression_of (s));
}

static_assert (if_with (^^cond_decl, 4, 1));
static_assert (if_with (^^init_decl, 4, 1));
static_assert (if_with (^^init_and_cond, 5, 2));
static_assert (if_with (^^destroyed, 4, 1));
static_assert (if_with (^^block_decl, 3, 0));
static_assert (if_with (^^nested, 4, 1));
static_assert (if_with (^^in_template<int>, 4, 1));
static_assert (if_with (^^in_template<long>, 4, 1));

// The block that holds a declaration is still a compound statement.
static_assert (is_compound_statement (statements_of (first (^^block_decl))[1]));
static_assert (statements_of (statements_of (first (^^block_decl))[1]).size ()
	       == 2);

// An if in a block is one of its statements.
consteval info
inner_if ()
{
  info block = statements_of (first (^^nested))[2];
  auto s = statements_of (block);
  return s.size () == 2 ? s[1] : info {};
}
static_assert (is_statement (inner_if ()) && !is_compound_statement (inner_if ()));
static_assert (statements_of (inner_if ()).size () == 4);
static_assert (is_declaration_statement (statements_of (inner_if ())[0]));

// The if is equal only to itself.
static_assert (first (^^cond_decl) == first (^^cond_decl));
static_assert (first (^^cond_decl) != first (^^init_decl));
static_assert (first (^^in_template<int>) != first (^^in_template<long>));
