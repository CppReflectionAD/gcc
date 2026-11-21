// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection -g -gstatement-frontiers -Wno-empty-body" }
// With statement frontiers, the body of a loop that isn't a block is still
// that statement, not a compound statement holding a debug marker and it,
// and a null statement body is still a null statement.

#include <meta>
#include <string>

using namespace std::meta;

int sink (int);

void
no_block (int x)
{
  for (int i = 0; i < x; ++i)
    sink (i);
  while (x < 10)
    ++x;
  do
    --x;
  while (x > 0);
}

void
null_body (int x)
{
  for (;;)
    ;
  while (sink (x))
    ;
}

void
block (int x)
{
  for (int i = 0; i < x; ++i)
    {
      sink (i);
      sink (x);
    }
  while (x < 10)
    {
      ++x;
    }
  do
    {
    }
  while (sink (x));
}

void
nested (int x)
{
  while (sink (x))
    for (std::string t = "a"; sink (x); ++x)
      sink (x);
}

template <typename T>
void
tmpl (T x)
{
  while (x < 10)
    ++x;
}

consteval info
stmt (info fn, int k)
{
  return statements_of (body_of (fn))[k];
}

static_assert (is_expression_statement (loop_body_of (stmt (^^no_block, 0))));
static_assert (is_expression_statement (loop_body_of (stmt (^^no_block, 1))));
static_assert (is_expression_statement (loop_body_of (stmt (^^no_block, 2))));
static_assert (!is_compound_statement (loop_body_of (stmt (^^no_block, 0))));
static_assert (!is_compound_statement (loop_body_of (stmt (^^no_block, 1))));
static_assert (!is_compound_statement (loop_body_of (stmt (^^no_block, 2))));

constexpr info for_null = loop_body_of (stmt (^^null_body, 0));
constexpr info while_null = loop_body_of (stmt (^^null_body, 1));
static_assert (is_expression_statement (for_null));
static_assert (is_expression_statement (while_null));
static_assert (!is_compound_statement (for_null));
static_assert (!is_compound_statement (while_null));
static_assert (for_null == loop_body_of (stmt (^^null_body, 0)));

static_assert (is_compound_statement (loop_body_of (stmt (^^block, 0))));
static_assert (statements_of (loop_body_of (stmt (^^block, 0))).size () == 2);
static_assert (is_compound_statement (loop_body_of (stmt (^^block, 1))));
static_assert (statements_of (loop_body_of (stmt (^^block, 1))).size () == 1);
static_assert (is_compound_statement (loop_body_of (stmt (^^block, 2))));
static_assert (statements_of (loop_body_of (stmt (^^block, 2))).empty ());

static_assert (is_for_statement (loop_body_of (stmt (^^nested, 0))));
static_assert (is_expression_statement
	       (loop_body_of (loop_body_of (stmt (^^nested, 0)))));

static_assert (is_expression_statement (loop_body_of (stmt (^^tmpl<int>, 0))));
