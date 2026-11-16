// { dg-do run { target c++26 } }
// { dg-additional-options "-freflection -O2" }
// A null statement's marker changes nothing about what a function does,
// including in a constant evaluation and with a label or a case before it.

constexpr int
f (int x)
{
  ;
  switch (x)
    {
    case 1: ;
    case 2: x += 1; ;
      break;
    default: ;
    }
  { ; }
  if (x > 100) ; else ;
  return x; ;
}

static_assert (f (1) == 2);
static_assert (f (5) == 5);

template <class T>
T
g (T x)
{
  ;
  auto l = [] (T y) { ; return y + 1; ; };
  ;
  return l (x);
}

int
main ()
{
  if (f (1) != 2 || f (5) != 5 || g (1) != 2)
    __builtin_abort ();
}
