// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// cpp_reflection_ad#268: a plain `if` with a constant condition is one
// statement, as one with a condition that isn't constant is, whichever of its
// statements the condition selects.

#include <meta>

using namespace std::meta;

int sink (int);

int
then_block (int x)
{
  if (true)
    { sink (x); }
  return 0;
}

int
then_no_else (int x)
{
  if (true)
    sink (x);
  return 0;
}

int
then_pure_else (int x)
{
  if (true)
    sink (x);
  else
    (void) x;
  return 0;
}

int
then_null_else (int x)
{
  if (true)
    sink (x);
  else
    ;
  return 0;
}

int
two_in_block (int x)
{
  if (sizeof (int) >= 2)
    { sink (x); sink (1); }
  return 0;
}

int
false_empty (int x)
{
  if (false)
    {}
  return x;
}

int
false_else (int x)
{
  if (false)
    {}
  else
    sink (x);
  return 0;
}

int
nested (int x)
{
  if (true)
    {
      sink (1);
      if (false)
	{}
      else
	sink (x);
    }
  return 0;
}

template <typename T> int
in_template (T x)
{
  if (sizeof (T) >= 2)
    return x;
  return 0;
}

constexpr int
in_constexpr (int x)
{
  if (true)
    return x;
  return 0;
}

static_assert (in_constexpr (3) == 3);

int
not_constant (int x)
{
  if (x)
    sink (x);
  return 0;
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

consteval bool
if_then_return (info fn)
{
  auto s = stmts (fn);
  return (s.size () == 2
	  && other_statement (s[0])
	  && is_return_statement (s[1]));
}

static_assert (if_then_return (^^then_block));
static_assert (if_then_return (^^then_no_else));
static_assert (if_then_return (^^then_pure_else));
static_assert (if_then_return (^^then_null_else));
static_assert (if_then_return (^^two_in_block));
static_assert (if_then_return (^^false_empty));
static_assert (if_then_return (^^false_else));
static_assert (if_then_return (^^nested));
static_assert (if_then_return (^^in_template<int>));
static_assert (if_then_return (^^in_template<char>));
static_assert (if_then_return (^^in_constexpr));
static_assert (if_then_return (^^not_constant));

// The inner `if` is a statement of the outer one's block.
static_assert (stmts (^^nested)[0] != stmts (^^false_else)[0]);
static_assert (other_statement
		 (statements_of (statements_of (stmts (^^nested)[0])[1])[1]));

// The condition and the statements of the `if`, an `else` included where
// there is one.
static_assert (statements_of (stmts (^^then_no_else)[0]).size () == 2);
static_assert (statements_of (stmts (^^then_null_else)[0]).size () == 3);
static_assert (statements_of (stmts (^^false_else)[0]).size () == 3);
static_assert (is_expression_statement
		 (statements_of (stmts (^^false_else)[0])[2]));

// The statement the condition doesn't select is still there.
static_assert (statements_of (stmts (^^then_pure_else)[0]).size () == 3);
static_assert (is_expression_statement
		 (statements_of (stmts (^^then_pure_else)[0])[2]));

// Two `if` statements that are alike are still two statements.
static_assert (stmts (^^then_block)[0] == stmts (^^then_block)[0]);
static_assert (stmts (^^then_no_else)[0] != stmts (^^then_null_else)[0]);
static_assert (stmts (^^in_template<int>)[0] != stmts (^^in_template<long>)[0]);
