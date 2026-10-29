// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// Test std::meta::is_compound_statement (P4395R0).

#include <meta>

using namespace std::meta;

void empty_fn () {}

constexpr int single_ret () {
  return 42;
}

constexpr int multi_stmt (int x) {
  int a = x + 1;
  return a;
}

template <typename T>
constexpr T tmpl_fn (T x) {
  return x * 2;
}

constexpr int nested_blocks (int x) {
  int acc = x;
  {
    int y = acc + 1;
    acc = y * 2;
  }
  {
    int z = 3;
    acc += z;
  }
  return acc;
}

constexpr int if_branches (int x) {
  int res = 0;
  if (x > 0) {
    res = x;
    res += 1;
  } else
    res = -x;
  return res;
}

int global_var = 0;

// Function bodies are compound statements.
static_assert (is_compound_statement (body_of (^^empty_fn)));
static_assert (is_statement (body_of (^^empty_fn)));
static_assert (!is_expression (body_of (^^empty_fn)));
static_assert (statements_of (body_of (^^empty_fn)).empty ());

static_assert (is_compound_statement (body_of (^^single_ret)));
static_assert (is_statement (body_of (^^single_ret)));
static_assert (!is_return_statement (body_of (^^single_ret)));
static_assert (statements_of (body_of (^^single_ret)).size () == 1);
static_assert (is_return_statement (statements_of (body_of (^^single_ret))[0]));
static_assert (!is_compound_statement (statements_of (body_of (^^single_ret))[0]));

static_assert (is_compound_statement (body_of (^^multi_stmt)));
static_assert (statements_of (body_of (^^multi_stmt)).size () == 2);
static_assert (is_declaration_statement (statements_of (body_of (^^multi_stmt))[0]));
static_assert (!is_compound_statement (statements_of (body_of (^^multi_stmt))[0]));
static_assert (is_return_statement (statements_of (body_of (^^multi_stmt))[1]));
static_assert (!is_compound_statement (statements_of (body_of (^^multi_stmt))[1]));

static_assert (is_compound_statement (body_of (^^tmpl_fn<int>)));

// Nested compound statements.
consteval bool test_nested_blocks () {
  auto stmts = statements_of (body_of (^^nested_blocks));
  if (stmts.size () != 4)
    return false;
  if (is_compound_statement (stmts[0]) || !is_declaration_statement (stmts[0]))
    return false;
  if (!is_compound_statement (stmts[1]) || !is_statement (stmts[1]))
    return false;
  if (statements_of (stmts[1]).size () != 2)
    return false;
  if (!is_compound_statement (stmts[2]) || !is_statement (stmts[2]))
    return false;
  if (statements_of (stmts[2]).size () != 2)
    return false;
  if (is_compound_statement (stmts[3]) || !is_return_statement (stmts[3]))
    return false;
  return true;
}
static_assert (test_nested_blocks ());

// Compound vs single-statement branches in an if statement.
consteval bool test_if_branches () {
  auto stmts = statements_of (body_of (^^if_branches));
  if (stmts.size () != 3)
    return false;
  auto branches = statements_of (stmts[1]);
  if (branches.size () != 3)
    return false;
  // Condition is not a compound statement.
  if (is_compound_statement (branches[0]))
    return false;
  // Then-branch is `{ res = x; res += 1; }` (compound statement).
  if (!is_compound_statement (branches[1]))
    return false;
  if (statements_of (branches[1]).size () != 2)
    return false;
  // Else-branch is `res = -x;` (not a compound statement).
  if (is_compound_statement (branches[2]))
    return false;
  return true;
}
static_assert (test_if_branches ());

// Negative cases: non-statements and other statement/expression kinds.
static_assert (!is_compound_statement (info{}));
static_assert (!is_compound_statement (^^int));
static_assert (!is_compound_statement (^^single_ret));
static_assert (!is_compound_statement (^^tmpl_fn));
static_assert (!is_compound_statement (^^global_var));
static_assert (!is_compound_statement (^^::));
static_assert (!is_compound_statement (return_operand_of (statements_of (body_of (^^single_ret))[0])));

// GNU statement-expression `({ ... })` is an expression, not a statement
// or compound statement.
constexpr double
stmt_expr_fn (double x)
{
  return __extension__ ({ double t = x; t * 2; });
}

constexpr info ret_stmt = statements_of (body_of (^^stmt_expr_fn))[0];
constexpr info ret_expr = return_operand_of (ret_stmt);
static_assert (is_expression (ret_expr));
static_assert (!is_statement (ret_expr));
static_assert (!is_compound_statement (ret_expr));

constexpr void
stmt_expr_stmt (int x)
{
  __extension__ ({ int t = x; t + 1; });
}

constexpr info es = statements_of (body_of (^^stmt_expr_stmt))[0];
static_assert (is_expression_statement (es));
static_assert (!is_compound_statement (es));
static_assert (is_expression (expression_of (es)));
static_assert (!is_statement (expression_of (es)));
