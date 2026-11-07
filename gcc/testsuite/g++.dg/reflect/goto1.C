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
static_assert(statements_of(body_of(^^jumps)).size() == 8);
static_assert(is_label_statement(stmt(^^jumps, 1)));
static_assert(is_statement(stmt(^^jumps, 1)));
static_assert(!is_goto_statement(stmt(^^jumps, 1)));
static_assert(identifier_of(label_of(stmt(^^jumps, 1))) == "again");

// `if (y < 10) goto again;`: the then-branch is the goto itself.
static_assert(is_if_statement(stmt(^^jumps, 3)));
static_assert(is_goto_statement(true_expression_of(stmt(^^jumps, 3))));
static_assert(label_of(true_expression_of(stmt(^^jumps, 3)))
	      == label_of(stmt(^^jumps, 1)));

// `goto done;` then `done:`.
static_assert(is_goto_statement(stmt(^^jumps, 5)));
static_assert(is_statement(stmt(^^jumps, 5)));
static_assert(!is_expression(stmt(^^jumps, 5)));
static_assert(is_label_statement(stmt(^^jumps, 6)));
static_assert(label_of(stmt(^^jumps, 5)) == label_of(stmt(^^jumps, 6)));
static_assert(identifier_of(label_of(stmt(^^jumps, 6))) == "done");

// Different labels compare unequal.
static_assert(label_of(stmt(^^jumps, 5)) != label_of(stmt(^^jumps, 1)));

// The lowered while: [goto C, B:, body, C:, if (c) goto B; else goto X;, X:].
// The labels have no identifier, but the gotos can be matched to them.
static_assert(is_goto_statement(nested(^^w, 1, 0)));
static_assert(is_label_statement(nested(^^w, 1, 1)));
static_assert(is_label_statement(nested(^^w, 1, 3)));
static_assert(is_if_statement(nested(^^w, 1, 4)));
static_assert(is_label_statement(nested(^^w, 1, 5)));
static_assert(!has_identifier(label_of(nested(^^w, 1, 1))));
static_assert(label_of(nested(^^w, 1, 0)) == label_of(nested(^^w, 1, 3)));
static_assert(label_of(true_expression_of(nested(^^w, 1, 4)))
	      == label_of(nested(^^w, 1, 1)));
static_assert(label_of(false_expression_of(nested(^^w, 1, 4)))
	      == label_of(nested(^^w, 1, 5)));

// A break jumps to the loop's exit label, the target of the condition's else.
static_assert(is_if_statement(nested(^^w_break, 1, 2)));
static_assert(label_of(true_expression_of(nested(^^w_break, 1, 2)))
	      == label_of(false_expression_of(nested(^^w_break, 1, 5))));
static_assert(label_of(true_expression_of(nested(^^w_break, 1, 2)))
	      != label_of(true_expression_of(nested(^^w_break, 1, 5))));

// Neither a goto nor a label.
static_assert(!is_goto_statement(^^int));
static_assert(!is_label_statement(^^jumps));
static_assert(!is_goto_statement(stmt(^^jumps, 0)));
static_assert(!is_label_statement(stmt(^^jumps, 7)));

consteval bool label_of_rejects() {
  try {
    label_of(stmt(^^jumps, 0));
    return false;
  } catch (const std::meta::exception &) {
  }
  return true;
}
static_assert(label_of_rejects());
