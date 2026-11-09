// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// Test is_try_statement, try_body_of, handlers_of, is_handler,
// handler_body_of and exception_declaration_of.

#include <meta>

using namespace std::meta;

struct E { int code; };

int may_throw(int x) {
  if (x < 0)
    throw x;
  return x;
}

int two_handlers(int x) {
  int y = 0;
  try {
    y = may_throw(x);
    y = y + 1;
  } catch (int e) {
    y = e;
  } catch (...) {
    y = -1;
  }
  return y;
}

// Blocks of one statement, an unnamed exception-declaration, and a
// reference.
int one_statement(int x) {
  int y = 0;
  try {
    y = may_throw(x);
  } catch (int) {
    y = 2;
  } catch (const E &err) {
    y = err.code;
    y = y * 2;
  }
  return y;
}

consteval info stmt(info fn, int k) {
  return statements_of(body_of(fn))[k];
}

// The Ith handler of the try block that is FN's Kth statement.  (A statement
// can't be a template argument, so not define_static_array.)
consteval info handler(info fn, int k, int i) {
  return handlers_of(stmt(fn, k))[i];
}

// The try block, between the declaration and the return.
static_assert(statements_of(body_of(^^two_handlers)).size() == 3);
static_assert(is_try_statement(stmt(^^two_handlers, 1)));
static_assert(is_statement(stmt(^^two_handlers, 1)));
static_assert(!is_try_statement(stmt(^^two_handlers, 0)));
static_assert(!is_try_statement(stmt(^^two_handlers, 2)));

// Its compound-statement.
constexpr info body = try_body_of(stmt(^^two_handlers, 1));
static_assert(is_compound_statement(body));
static_assert(statements_of(body).size() == 2);
static_assert(is_expression_statement(statements_of(body)[0]));
static_assert(is_expression_statement(statements_of(body)[1]));

// Its handlers, in order.
static_assert(handlers_of(stmt(^^two_handlers, 1)).size() == 2);
constexpr info hs[] = {handler(^^two_handlers, 1, 0),
		       handler(^^two_handlers, 1, 1)};
static_assert(is_handler(hs[0]) && is_handler(hs[1]));
static_assert(is_statement(hs[0]));

// catch (int e): e is the exception-declaration, and the body is just
// `y = e;`, without the call of __cxa_begin_catch, its temporary or e.
static_assert(is_variable(exception_declaration_of(hs[0])));
static_assert(identifier_of(exception_declaration_of(hs[0])) == "e");
static_assert(type_of(exception_declaration_of(hs[0])) == ^^int);
static_assert(is_compound_statement(handler_body_of(hs[0])));
static_assert(statements_of(handler_body_of(hs[0])).size() == 1);
static_assert(is_expression_statement(statements_of(handler_body_of(hs[0]))[0]));

// catch (...): no exception-declaration.
static_assert(exception_declaration_of(hs[1]) == info{});
static_assert(is_compound_statement(handler_body_of(hs[1])));
static_assert(statements_of(handler_body_of(hs[1])).size() == 1);

// A block of one statement is still a compound statement.
constexpr info one = try_body_of(stmt(^^one_statement, 1));
static_assert(is_compound_statement(one));
static_assert(statements_of(one).size() == 1);
static_assert(is_expression_statement(statements_of(one)[0]));

static_assert(handlers_of(stmt(^^one_statement, 1)).size() == 2);
constexpr info hs1[] = {handler(^^one_statement, 1, 0),
			handler(^^one_statement, 1, 1)};

// catch (int): a variable with no identifier.
static_assert(is_variable(exception_declaration_of(hs1[0])));
static_assert(!has_identifier(exception_declaration_of(hs1[0])));
static_assert(statements_of(handler_body_of(hs1[0])).size() == 1);

// catch (const E &err).
static_assert(identifier_of(exception_declaration_of(hs1[1])) == "err");
static_assert(type_of(exception_declaration_of(hs1[1])) == ^^const E &);
static_assert(statements_of(handler_body_of(hs1[1])).size() == 2);

// Neither a try block nor a handler.
static_assert(!is_try_statement(^^int));
static_assert(!is_handler(stmt(^^two_handlers, 1)));
static_assert(!is_handler(^^two_handlers));

consteval bool rejects() {
  try {
    try_body_of(stmt(^^two_handlers, 0));
    return false;
  } catch (const std::meta::exception &) {
  }
  try {
    handler_body_of(stmt(^^two_handlers, 1));
    return false;
  } catch (const std::meta::exception &) {
  }
  try {
    exception_declaration_of(^^int);
    return false;
  } catch (const std::meta::exception &) {
  }
  return true;
}
static_assert(rejects());
