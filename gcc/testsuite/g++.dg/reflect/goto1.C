// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// Test is_goto_statement, is_label_statement and label_of, on written gotos
// and labels and on the ones a lowered loop is made of.

#include <meta>

using namespace std::meta;

int jumps(int x) {
  int y = x;
again:
  y = y + 1;
  if (y < 10)
    goto again;
  y = y * 2;
  goto done;
done:
  return y;
}

constexpr int w(int x) {
  int y = x;
  while (y < 10)
    y = y * 2;
  return y;
}

constexpr int w_break(int x) {
  int y = x;
  while (y < 10) {
    if (y > 5)
      break;
    y = y * 2;
  }
  return y;
}

consteval info stmt(info fn, int k) {
  return statements_of(body_of(fn))[k];
}

consteval info nested(info fn, int k, int j) {
  return statements_of(stmt(fn, k))[j];
}

// The written gotos and labels, and nothing the front end adds for them.
// A labeled statement is one statement, of the statement it labels.
static_assert(statements_of(body_of(^^jumps)).size() == 6);
static_assert(is_label_statement(stmt(^^jumps, 1)));
static_assert(is_statement(stmt(^^jumps, 1)));
static_assert(!is_goto_statement(stmt(^^jumps, 1)));
static_assert(identifier_of(label_of(stmt(^^jumps, 1))) == "again");
static_assert(statements_of(stmt(^^jumps, 1)).size() == 1);
static_assert(is_expression_statement(nested(^^jumps, 1, 0)));

// `if (y < 10) goto again;`: the then-branch is the goto itself.
static_assert(is_if_statement(stmt(^^jumps, 2)));
static_assert(is_goto_statement(true_expression_of(stmt(^^jumps, 2))));
static_assert(label_of(true_expression_of(stmt(^^jumps, 2)))
	      == label_of(stmt(^^jumps, 1)));

// `goto done;` then `done:`.
static_assert(is_goto_statement(stmt(^^jumps, 4)));
static_assert(is_statement(stmt(^^jumps, 4)));
static_assert(!is_expression(stmt(^^jumps, 4)));
static_assert(is_label_statement(stmt(^^jumps, 5)));
static_assert(label_of(stmt(^^jumps, 4)) == label_of(stmt(^^jumps, 5)));
static_assert(identifier_of(label_of(stmt(^^jumps, 5))) == "done");
static_assert(is_return_statement(nested(^^jumps, 5, 0)));

// Different labels compare unequal.
static_assert(label_of(stmt(^^jumps, 4)) != label_of(stmt(^^jumps, 1)));

// Under Option 2, loops and break remain first-class statements rather than
// lowered gotos and labels.
static_assert(is_while_statement(stmt(^^w, 1)));
static_assert(!is_goto_statement(stmt(^^w, 1)));
static_assert(is_while_statement(stmt(^^w_break, 1)));
static_assert(is_break_statement(true_expression_of(statements_of(loop_body_of(stmt(^^w_break, 1)))[0])));

// Neither a goto nor a label.
static_assert(!is_goto_statement(^^int));
static_assert(!is_label_statement(^^jumps));
static_assert(!is_goto_statement(stmt(^^jumps, 0)));
static_assert(!is_label_statement(nested(^^jumps, 5, 0)));

consteval bool label_of_rejects() {
  try {
    label_of(stmt(^^jumps, 0));
    return false;
  } catch (const std::meta::exception &) {
  }
  return true;
}
static_assert(label_of_rejects());
