// { dg-do run { target c++17 } }

int state;

struct F
{
  int k;
  int operator() (int x) const
  {
    if (state != 2)
      __builtin_abort ();
    return k + x;
  }
};

F
make_f ()
{
  if (state != 0)
    __builtin_abort ();
  state = 1;
  return { 1 };
}

int
arg (int i)
{
  if (state != 1)
    __builtin_abort ();
  state = 2;
  return i;
}

int
main ()
{
  int res = make_f () (arg (1));
  if (state != 2 || res != 2)
    __builtin_abort ();
}
