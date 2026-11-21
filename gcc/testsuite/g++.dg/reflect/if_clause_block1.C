// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// cpp_reflection_ad#269: a block that is the then or else statement of an
// `if` is a compound statement, whatever it holds.

#include <meta>

using namespace std::meta;

int sink (int);

int
one (int x)
{
  if (x)
    { sink (x); }
  return 0;
}

int
two (int x)
{
  if (x)
    { sink (x); sink (1); }
  return 0;
}

int
empty (int x)
{
  if (x)
    {}
  return 0;
}

int
else_one (int x)
{
  if (x)
    sink (1);
  else
    { sink (x); }
  return 0;
}

int
no_block (int x)
{
  if (x)
    sink (x);
  else
    sink (1);
  return 0;
}

int
else_if (int x)
{
  if (x)
    { sink (x); }
  else if (x + 1)
    { sink (1); }
  return 0;
}

int
constant (int x)
{
  if (true)
    { sink (x); }
  return 0;
}

template <typename T> int
in_template (T x)
{
  if (x)
    { sink (x); }
  else
    {}
  if constexpr (sizeof (T) >= 2)
    { sink (1); }
  return 0;
}

consteval auto
stmts (info fn)
{
  return statements_of (body_of (fn));
}

consteval info
part (info fn, int i, int j = 0)
{
  return statements_of (stmts (fn)[j])[i];
}

// The then statement of each `if`.
static_assert (is_compound_statement (part (^^one, 1)));
static_assert (is_compound_statement (part (^^two, 1)));
static_assert (is_compound_statement (part (^^empty, 1)));
static_assert (is_expression_statement (part (^^else_one, 1)));
static_assert (is_expression_statement (part (^^no_block, 1)));
static_assert (is_compound_statement (part (^^else_if, 1)));
static_assert (is_compound_statement (part (^^constant, 1)));
static_assert (is_compound_statement (part (^^in_template<int>, 1)));
static_assert (is_compound_statement (part (^^in_template<int>, 1, 1)));

// The else statement.
static_assert (is_compound_statement (part (^^else_one, 2)));
static_assert (is_expression_statement (part (^^no_block, 2)));
static_assert (is_compound_statement (part (^^in_template<int>, 2)));
static_assert (is_compound_statement
		 (statements_of (part (^^else_if, 2))[1]));

// The statements of each block.
static_assert (statements_of (part (^^one, 1)).size () == 1);
static_assert (is_expression_statement (statements_of (part (^^one, 1))[0]));
static_assert (statements_of (part (^^two, 1)).size () == 2);
static_assert (statements_of (part (^^empty, 1)).size () == 0);
static_assert (statements_of (part (^^else_one, 2)).size () == 1);
static_assert (statements_of (part (^^in_template<int>, 2)).size () == 0);

// An `if` is equal only to itself, however alike another is.
static_assert (stmts (^^one)[0] == stmts (^^one)[0]);
static_assert (stmts (^^one)[0] != stmts (^^constant)[0]);
static_assert (stmts (^^two)[0] != stmts (^^one)[0]);
static_assert (stmts (^^else_if)[0] != stmts (^^one)[0]);

// The `if` statements are still the statements of the body.
static_assert (stmts (^^one).size () == 2);
static_assert (stmts (^^in_template<int>).size () == 3);
