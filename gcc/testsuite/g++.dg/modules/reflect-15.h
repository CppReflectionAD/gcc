// cpp_reflection_ad#287: a labeled statement reaches an importer of the body
// as one statement, as does a `switch' with a braced body.

#include <meta>

using namespace std::meta;

struct D { ~D () {} };

inline int
labeled (int x)
{
a:
  D d;
  if (x > 1)
    {
      x--;
      goto a;
    }
  switch (x) { x++; }
  if (x)
  b: x++;
  return x;
}

// FN's body is `a: D d;', an if, a switch with a braced body and an if whose
// then statement is labeled `b', and a return.
consteval bool
labeled_shape (info fn)
{
  auto s = statements_of (body_of (fn));
  if (s.size () != 5 || !is_label_statement (s[0]))
    return false;
  auto a = statements_of (s[0]);
  auto sw = statements_of (s[2]);
  info b = then_statement_of (s[3]);
  return (a.size () == 1 && is_declaration_statement (a[0])
	  && identifier_of (label_of (s[0])) == "a"
	  && sw.size () == 2 && is_compound_statement (sw[1])
	  && statements_of (sw[1]).size () == 1
	  && is_label_statement (b) && identifier_of (label_of (b)) == "b"
	  && b == statements_of (s[3])[1]
	  && is_expression_statement (statements_of (b)[0])
	  && is_return_statement (s[4]));
}
