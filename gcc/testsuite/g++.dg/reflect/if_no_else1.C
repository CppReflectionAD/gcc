// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// cpp_reflection_ad#270: an `if` with no `else` has no else part, though
// genericize_if_stmt gives its COND_EXPR an empty statement for one.

#include <meta>

using namespace std::meta;

int sink (int);

int
no_else (int x)
{
  if (x)
    sink (x);
  return 0;
}

int
with_else (int x)
{
  if (x)
    sink (x);
  else
    sink (2);
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
block_no_else (int x)
{
  if (x)
    {
      sink (x);
      sink (1);
    }
  return 0;
}

int
else_if_no_else (int x)
{
  if (x)
    sink (x);
  else if (x + 1)
    sink (1);
  return 0;
}

template <typename T> int
in_template (T x)
{
  if (x)
    sink (x);
  return 0;
}

consteval info
if0 (info fn)
{
  return statements_of (body_of (fn))[0];
}

consteval std::size_t
parts (info s)
{
  return statements_of (s).size ();
}

consteval bool
has_false_expression (info s)
{
  try
    {
      false_expression_of (s);
      return true;
    }
  catch (const std::meta::exception &)
    {
      return false;
    }
}

// The condition and the `then`, and the `else` where there is one.
static_assert (parts (if0 (^^no_else)) == 2);
static_assert (parts (if0 (^^with_else)) == 3);
static_assert (parts (if0 (^^null_else)) == 3);
static_assert (parts (if0 (^^block_no_else)) == 2);
static_assert (parts (if0 (^^in_template<int>)) == 2);

// The `then` is the last part of an `if` with no `else`.
static_assert (is_expression_statement
		 (statements_of (if0 (^^no_else))[1]));

// An `else if` is the `else` of the outer `if`, and the inner one has no
// `else`.
static_assert (parts (if0 (^^else_if_no_else)) == 3);
static_assert (parts (statements_of (if0 (^^else_if_no_else))[2]) == 2);

// false_expression_of gives the `else` where there is one.
static_assert (!has_false_expression (if0 (^^no_else)));
static_assert (has_false_expression (if0 (^^with_else)));
static_assert (!has_false_expression (if0 (^^in_template<int>)));
