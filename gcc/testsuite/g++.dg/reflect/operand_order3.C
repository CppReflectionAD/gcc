// { dg-do run { target c++26 } }
// { dg-additional-options "-freflection" }
// The operators kept as written for reflection still compute the right
// values.

[[gnu::noipa]] int
f (int x, int y, bool a, bool b, double d, int p)
{
  int r = 0;
  if (x - x != 0)
    r |= 1;
  if (!(a || b) != (!a && !b))
    r |= 2;
  if (!(x < y) != (x >= y))
    r |= 4;
  if (!!a != a)
    r |= 8;
  if (x + 0 != x || x * 1 != x)
    r |= 16;
  if ((true && a) != a)
    r |= 32;
  if (d + p != p + d || 2.0 * d != d * 2.0)
    r |= 64;
  return r;
}

int
main ()
{
  for (int x = -2; x <= 2; ++x)
    for (int y = -2; y <= 2; ++y)
      for (int m = 0; m < 4; ++m)
	if (f (x, y, m & 1, m & 2, x * 0.5, y) != 0)
	  __builtin_abort ();
}
