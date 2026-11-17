// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection -g -gstatement-frontiers -Wno-empty-body" }
// cpp_reflection_ad#279: with statement frontiers, a statement that is the
// then or else statement of an if, and isn't a block, is still that
// statement, not a compound statement holding a debug marker and it.

#include <meta>

using namespace std::meta;

int sink (int);

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
two_block (int x)
{
  if (x)
    {
      sink (x);
      sink (1);
    }
  return 0;
}

int
null_else (int x)
{
  if (x)
    sink (x);
  else
    ;
  return 0;
}

int
constant (int x)
{
  if (true)
    sink (x);
  return 0;
}

int
ret_then (int x)
{
  if (x)
    return 1;
  return 0;
}

int
else_if (int x)
{
  if (x)
    sink (x);
  else if (x + 1)
    sink (1);
  else
    sink (2);
  return 0;
}

template <typename T> int
in_template (T x)
{
  if (x)
    sink (x);
  else
    return 1;
  return 0;
}

consteval info
first (info fn)
{
  return statements_of (body_of (fn))[0];
}

consteval info
part (info fn, int i)
{
  return statements_of (first (fn))[i];
}

static_assert (is_expression_statement (part (^^no_block, 1)));
static_assert (is_expression_statement (part (^^no_block, 2)));
static_assert (is_expression_statement (true_expression_of (first (^^no_block))));
static_assert (is_expression_statement (false_expression_of (first (^^no_block))));
static_assert (!is_compound_statement (part (^^null_else, 2)));
static_assert (is_expression_statement (part (^^constant, 1)));
static_assert (is_return_statement (part (^^ret_then, 1)));
static_assert (is_expression_statement (part (^^in_template<int>, 1)));
static_assert (is_return_statement (part (^^in_template<int>, 2)));

// An `else if` is the `if` itself, whose parts are statements too.
static_assert (!is_compound_statement (part (^^else_if, 2)));
static_assert (statements_of (part (^^else_if, 2)).size () == 3);
static_assert (is_expression_statement (statements_of (part (^^else_if, 2))[1]));
static_assert (is_expression_statement (statements_of (part (^^else_if, 2))[2]));

// A block of two statements is still a compound statement of two.
static_assert (is_compound_statement (part (^^two_block, 1)));
static_assert (statements_of (part (^^two_block, 1)).size () == 2);
