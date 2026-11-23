// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection -Wno-empty-body" }
// A null statement is a statement, so a reflection of one is equal only to
// a reflection of the same null statement.  Comparing two used to ICE.

#include <meta>

using namespace std::meta;

int sink (int);

void two_nulls () { ; ; }
void one_null () { ; }
void loops (int x) { for (;;) ; while (sink (x)) ; }
void ifs (int x) { if (x) ; else ; }
template <int N> void tmpl () { ; ; }

consteval info
st (info fn, int k)
{
  return statements_of (body_of (fn))[k];
}

static_assert (st (^^two_nulls, 0) == st (^^two_nulls, 0));
static_assert (st (^^two_nulls, 0) != st (^^two_nulls, 1));
static_assert (st (^^two_nulls, 0) != st (^^one_null, 0));

static_assert (loop_body_of (st (^^loops, 0)) == loop_body_of (st (^^loops, 0)));
static_assert (loop_body_of (st (^^loops, 0)) != loop_body_of (st (^^loops, 1)));
static_assert (loop_body_of (st (^^loops, 0)) != st (^^one_null, 0));

static_assert (then_statement_of (st (^^ifs, 0))
	       == then_statement_of (st (^^ifs, 0)));

static_assert (st (^^tmpl<1>, 0) == st (^^tmpl<1>, 0));
static_assert (st (^^tmpl<1>, 0) != st (^^tmpl<1>, 1));

// A constexpr variable holds a copy of the statement, which is still the
// same null statement.
constexpr info block_null = st (^^two_nulls, 0);
constexpr info loop_null = loop_body_of (st (^^loops, 0));
constexpr info then_null = then_statement_of (st (^^ifs, 0));
static_assert (block_null == st (^^two_nulls, 0));
static_assert (block_null != st (^^two_nulls, 1));
static_assert (loop_null == loop_body_of (st (^^loops, 0)));
static_assert (loop_null != loop_body_of (st (^^loops, 1)));
static_assert (then_null == then_statement_of (st (^^ifs, 0)));
static_assert (then_null != else_statement_of (st (^^ifs, 0)));

static_assert (st (^^one_null, 0) != ^^int);
static_assert (st (^^one_null, 0) != info {});
