// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection -Wno-vla -Wno-pedantic -Wno-switch-unreachable" }
// A labeled statement is one statement, as on clang: statements_of gives the
// statement it labels, after the value a case label matches
// (cpp_reflection_ad#287).  A variable with a destructor declared after a
// label isn't in a block of its own, while the scope of a `switch' that
// declares a variable is the `switch'.

#include <meta>
#include <string>

using namespace std::meta;

// The kinds of the statements in S, nested: C a block, L a label, If, S
// another statement with parts, D a declaration, R a return, B a break, E an
// expression or an expression statement.
consteval std::string
shape (info s)
{
  if (is_expression (s) || is_expression_statement (s))
    return "E";
  if (is_declaration_statement (s))
    return "D";
  if (is_return_statement (s))
    return "R";
  if (is_break_statement (s))
    return "B";
  std::string r = (is_compound_statement (s) ? "C"
		   : is_label_statement (s) ? "L"
		   : is_if_statement (s) ? "If" : "S");
  auto parts = statements_of (s);
  if (!parts.empty ())
    {
      r += "(";
      for (std::size_t i = 0; i < parts.size (); ++i)
	r += (i ? " " : "") + shape (parts[i]);
      r += ")";
    }
  return r;
}

consteval std::string
body_shape (info fn)
{
  return shape (body_of (fn));
}

struct T { ~T () {} };
int sink (int x) { return x; }

int
named (int x)
{
a:
  sink (x);
b: c:
  sink (x);
  return 0;
}

int
at_end (int x)
{
  {
    sink (x);
  e:
  }
  return 0;
}

int
before_decl (int x)
{
d:
  int y = x;
  return y;
}

int
before_class (int x)
{
c:
  T t;
  sink (x);
  return 0;
}

int
two_classes (int x)
{
c:
  T t, u;
  T v;
  sink (x);
  return 0;
}

int
class_after_label (int x)
{
k:
  sink (x);
  T t;
  sink (x);
  return 0;
}

int
class_after_block (int x)
{
  { k:; }
  T t;
  sink (x);
  return 0;
}

int
class_after_switch (int x)
{
  switch (x) { case 1: break; }
  T t;
  sink (x);
  return 0;
}

int
vla (int x)
{
v:
  int a[x];
  a[0] = x;
  return a[0];
}

int
cases (int x)
{
  switch (x)
    {
    case 1:
      sink (x);
      break;
    case 2:
    case 3:
      break;
    case 4 ... 6:
      sink (x);
    default:
      break;
    }
  return 0;
}

int
bare_switches (int x)
{
  switch (x) case 1: sink (x);
  switch (x) default: sink (x);
  switch (x) { sink (x); }
  return 0;
}

int
clauses (int x)
{
  if (x) l1: sink (x);
  if (x) { l2: sink (x); }
  if (x) sink (x); else l3: l4: sink (x);
  while (x) l5: sink (x--);
  while (x) { l6: sink (x--); }
  do l7: sink (x--); while (x);
  for (int i = 0; i < x; ++i) l8: sink (i);
  return 0;
}

int
braced (int x)
{
  while (x) { sink (x--); }
  do { sink (x--); } while (x);
  for (; x; ) { sink (x--); }
  return 0;
}

int
switch_scopes (int x)
{
s1:
  switch (int y = x) { case 1: sink (y); }
s2:
  T t;
  switch (T u; x) { default: sink (x); }
  return 0;
}

template <typename U>
U
tmpl (U x)
{
m:
  T t;
  sink (x);
  return x;
}

template int tmpl<int> (int);

static_assert (body_shape (^^named) == "C(L(E) L(L(E)) R)");
static_assert (body_shape (^^at_end) == "C(C(E L(E)) R)");
static_assert (body_shape (^^before_decl) == "C(L(D) R)");
static_assert (body_shape (^^before_class) == "C(L(D) E R)");
static_assert (body_shape (^^two_classes) == "C(L(D) D E R)");
static_assert (body_shape (^^class_after_label) == "C(L(E) D E R)");
static_assert (body_shape (^^class_after_block) == "C(C(L(E)) D E R)");
static_assert (body_shape (^^class_after_switch) == "C(S(E C(S(E B))) D E R)");
static_assert (body_shape (^^vla) == "C(L(D) E R)");
static_assert (body_shape (^^cases)
	       == "C(S(E C(S(E E) B S(E S(E B)) S(E E E) S(B))) R)");
static_assert (body_shape (^^bare_switches)
	       == "C(S(E S(E E)) S(E S(E)) S(E C(E)) R)");
static_assert (body_shape (^^clauses)
	       == "C(If(E L(E)) If(E C(L(E))) If(E E L(L(E))) S(E L(E))"
		  " S(E C(L(E))) S(L(E) E) S(D E E L(E)) R)");
static_assert (body_shape (^^braced) == "C(S(E C(E)) S(C(E) E) S(E C(E)) R)");
static_assert (body_shape (^^switch_scopes)
	       == "C(L(S(D E C(S(E E)))) L(D) S(D E C(S(E))) R)");
static_assert (body_shape (^^tmpl<int>) == "C(L(D) E R)");

consteval info
st (info fn, std::size_t i)
{
  return statements_of (body_of (fn))[i];
}

consteval bool
labels (info s, std::string_view name)
{
  return is_label_statement (s) && identifier_of (label_of (s)) == name;
}

// label_of of each label; the statement `b' labels is the one `c' does.
static_assert (labels (st (^^named, 0), "a"));
static_assert (labels (st (^^named, 1), "b"));
static_assert (labels (statements_of (st (^^named, 1))[0], "c"));
static_assert (is_expression_statement (statements_of (st (^^named, 0))[0]));

// A label at the end of a block labels a null statement.
static_assert (labels (statements_of (st (^^at_end, 0))[1], "e"));

// Two reflections of the statement a label labels compare equal.
static_assert (statements_of (st (^^named, 0))[0]
	       == statements_of (st (^^named, 0))[0]);
static_assert (statements_of (statements_of (st (^^at_end, 0))[1])[0]
	       == statements_of (statements_of (st (^^at_end, 0))[1])[0]);

// A case label isn't a label statement.
consteval info
switch_body (info fn, std::size_t i)
{
  return statements_of (st (fn, i))[1];
}
static_assert (!is_label_statement (statements_of (switch_body (^^cases, 0))[0]));
static_assert (!is_label_statement (switch_body (^^bare_switches, 0)));

// The then, else and loop body accessors give a labeled statement that
// isn't a block, as statements_of does.
static_assert (labels (then_statement_of (st (^^clauses, 0)), "l1"));
static_assert (then_statement_of (st (^^clauses, 0))
	       == statements_of (st (^^clauses, 0))[1]);
static_assert (is_compound_statement (then_statement_of (st (^^clauses, 1))));
static_assert (labels (else_statement_of (st (^^clauses, 2)), "l3"));
static_assert (labels (statements_of (else_statement_of (st (^^clauses, 2)))[0],
		       "l4"));
static_assert (labels (loop_body_of (st (^^clauses, 3)), "l5"));
static_assert (is_compound_statement (loop_body_of (st (^^clauses, 4))));
static_assert (labels (loop_body_of (st (^^clauses, 5)), "l7"));
static_assert (labels (loop_body_of (st (^^clauses, 6)), "l8"));
static_assert (loop_body_of (st (^^clauses, 6))
	       == statements_of (st (^^clauses, 6))[3]);

// A block that is the body of a loop is one with a single statement too.
static_assert (loop_body_of (st (^^braced, 0))
	       == statements_of (st (^^braced, 0))[1]);
static_assert (loop_body_of (st (^^braced, 1))
	       == statements_of (st (^^braced, 1))[0]);
