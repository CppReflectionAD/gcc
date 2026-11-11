// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// cpp_reflection_ad#250: an `if constexpr` is one statement, whichever of its
// statements is discarded and whatever else is in the body.

#include <meta>
#include <type_traits>

using namespace std::meta;

int sink (int);

template <typename T> void
whole_body (T)
{
  if constexpr (std::is_arithmetic_v<T>)
    { sink (1); sink (2); }
  else
    sink (3);
}

template <typename T> void
not_taken (T)
{
  if constexpr (!std::is_arithmetic_v<T>)
    sink (1);
}

template <typename T> int
then_return (T)
{
  if constexpr (std::is_arithmetic_v<T>)
    { sink (1); sink (2); }
  return 0;
}

template <typename T> int
one_then_return (T)
{
  if constexpr (std::is_arithmetic_v<T>)
    { sink (1); }
  return 0;
}

template <typename T> int
else_taken (T)
{
  if constexpr (!std::is_arithmetic_v<T>)
    return 1;
  else
    return sink (2);
}

template <typename T> int
chain (T)
{
  if constexpr (sizeof (T) == 1)
    return 1;
  else if constexpr (sizeof (T) == 4)
    return 4;
  else
    return 8;
}

int
not_a_template (int x)
{
  if constexpr (sizeof (int) >= 2)
    sink (x);
  else
    sink (0);
  return x;
}

consteval auto
stmts (info fn)
{
  return statements_of (body_of (fn));
}

// Some other statement: not an expression statement, a block, a return or a
// declaration.
consteval bool
other_statement (info s)
{
  return (is_statement (s)
	  && !is_expression (s)
	  && !is_expression_statement (s)
	  && !is_compound_statement (s)
	  && !is_return_statement (s)
	  && !is_declaration_statement (s));
}

static_assert (stmts (^^whole_body<int>).size () == 1);
static_assert (other_statement (stmts (^^whole_body<int>)[0]));
static_assert (stmts (^^whole_body<int *>).size () == 1);
static_assert (other_statement (stmts (^^whole_body<int *>)[0]));
static_assert (stmts (^^not_taken<int>).size () == 1);
static_assert (other_statement (stmts (^^not_taken<int>)[0]));
static_assert (stmts (^^then_return<int>).size () == 2);
static_assert (other_statement (stmts (^^then_return<int>)[0]));
static_assert (is_return_statement (stmts (^^then_return<int>)[1]));
static_assert (stmts (^^one_then_return<int>).size () == 2);
static_assert (other_statement (stmts (^^one_then_return<int>)[0]));
static_assert (stmts (^^else_taken<int>).size () == 1);
static_assert (other_statement (stmts (^^else_taken<int>)[0]));
static_assert (stmts (^^chain<char>).size () == 1);
static_assert (stmts (^^chain<int>).size () == 1);
static_assert (other_statement (stmts (^^chain<int>)[0]));
static_assert (stmts (^^not_a_template).size () == 2);
static_assert (other_statement (stmts (^^not_a_template)[0]));
static_assert (is_return_statement (stmts (^^not_a_template)[1]));

// Two `if` statements that are alike are still two statements.
static_assert (stmts (^^whole_body<int>)[0] == stmts (^^whole_body<int>)[0]);
static_assert (stmts (^^whole_body<int>)[0] != stmts (^^whole_body<long>)[0]);
static_assert (stmts (^^then_return<int>)[0] != stmts (^^one_then_return<int>)[0]);
