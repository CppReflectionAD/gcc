// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// A subscript of a pointer, `p[i]', which the front end builds as
// `*(p + i)', reflects as written: operator [] with the pointer and the
// index as operands.  So does pointer arithmetic, `p + i', as operator +.

#include <meta>

using namespace std::meta;

int read(const int *a, int i) { return a[i]; }
void write(int *a, int i, int v) { a[i] = v; }
int constant(const int *a) { return a[2]; }
int first(const int *a) { return a[0]; }
void write_first(int *a, int v) { a[0] = v; }
char bytes(const char *s, int i) { return s[i]; }
int mid(const int *a, int lo, int hi) { return a[lo + (hi - lo) / 2]; }
int before(const int *a, int j) { return a[j - 1]; }
int after(const int *a, int j) { return a[2 * j + 1]; }
int deref(const int *a, int i) { return *(a + i); }
int array(int i) {
  int b[4] = {1, 2, 3, 4};
  return b[i];
}

consteval info strip(info e) {
  while (is_conversion(e))
    e = operands_of(e)[0];
  return e;
}

consteval info ret(info fn) {
  for (info s : statements_of(body_of(fn)))
    if (is_return_statement(s))
      return strip(return_operand_of(s));
  throw "no return";
}

consteval bool names(info e, const char *name) {
  e = strip(e);
  return is_id_expression(e) && identifier_of(declaration_of(e)) == name;
}

// a[i]
constexpr info r = ret(^^read);
static_assert(is_operator_expression(r));
static_assert(is_binary_operator(r) && !is_unary_operator(r));
static_assert(operator_of(r) == operators::op_square_brackets);
static_assert(operands_of(r).size() == 2);
static_assert(names(operands_of(r)[0], "a"));
static_assert(names(operands_of(r)[1], "i"));

// a[i] = v: the left operand of the assignment is the subscript.
constexpr info w = strip(expression_of(statements_of(body_of(^^write))[0]));
static_assert(operator_of(w) == operators::op_equals);
static_assert(operator_of(strip(operands_of(w)[0]))
	      == operators::op_square_brackets);
static_assert(names(operands_of(strip(operands_of(w)[0]))[1], "i"));

// a[2]: the index is the constant.
constexpr info c = ret(^^constant);
static_assert(operator_of(c) == operators::op_square_brackets);
static_assert(is_literal(strip(operands_of(c)[1])));
static_assert(extract<long>(constant_of(strip(operands_of(c)[1]))) == 2);

// a[0]: adding the zero offset folds away, but it is still a subscript.
constexpr info f0 = ret(^^first);
static_assert(operator_of(f0) == operators::op_square_brackets);
static_assert(names(operands_of(f0)[0], "a"));
static_assert(extract<long>(constant_of(strip(operands_of(f0)[1]))) == 0);
constexpr info w0
  = strip(expression_of(statements_of(body_of(^^write_first))[0]));
static_assert(operator_of(strip(operands_of(w0)[0]))
	      == operators::op_square_brackets);

// s[i] for a char, whose size is 1, so there is no multiplication.
constexpr info b = ret(^^bytes);
static_assert(operator_of(b) == operators::op_square_brackets);
static_assert(names(operands_of(b)[1], "i"));

// a[lo + (hi - lo) / 2]: the index is the expression written.
constexpr info m = ret(^^mid);
static_assert(operator_of(m) == operators::op_square_brackets);
static_assert(operator_of(strip(operands_of(m)[1])) == operators::op_plus);
static_assert(names(operands_of(strip(operands_of(m)[1]))[0], "lo"));

// a[j - 1]: the front end folds the constant out of the byte offset, as
// `(sizetype) j * 4 - 4'; the index is still `j - 1'.
constexpr info bj = ret(^^before);
static_assert(operator_of(bj) == operators::op_square_brackets);
static_assert(operator_of(strip(operands_of(bj)[1])) == operators::op_minus);
static_assert(names(operands_of(strip(operands_of(bj)[1]))[0], "j"));
static_assert(extract<int>(constant_of(strip(operands_of(strip(operands_of(bj)[1]))[1]))) == 1);

// a[2 * j + 1]
constexpr info aj = ret(^^after);
static_assert(operator_of(aj) == operators::op_square_brackets);
static_assert(operator_of(strip(operands_of(aj)[1])) == operators::op_plus);
static_assert(operator_of(strip(operands_of(strip(operands_of(aj)[1]))[0]))
	      == operators::op_star);

// *(a + i) is a dereference of a sum, as written.
constexpr info d = ret(^^deref);
static_assert(operator_of(d) == operators::op_star);
static_assert(is_unary_operator(d));
constexpr info sum = strip(operands_of(d)[0]);
static_assert(operator_of(sum) == operators::op_plus);
static_assert(names(operands_of(sum)[0], "a"));
static_assert(names(operands_of(sum)[1], "i"));

// A subscript of an array was already an ARRAY_REF.
constexpr info arr = ret(^^array);
static_assert(operator_of(arr) == operators::op_square_brackets);
static_assert(names(operands_of(arr)[1], "i"));
