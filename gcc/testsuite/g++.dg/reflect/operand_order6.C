// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection -Wlogical-not-parentheses -Wsequence-point" }
// Keeping `!' as written for reflection doesn't change its warnings.

int
f (int a, int b, bool c)
{
  int r = 0;
  r += !a == b; // { dg-warning "logical not is only applied to the left hand side of comparison" }
  r += !a == (a < b);
  r += !!a == b;
  r += !c == b;
  a = ! (a++ && 4); // { dg-bogus "undefined" }
  return r;
}
