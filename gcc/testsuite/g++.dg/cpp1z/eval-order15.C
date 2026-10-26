// { dg-do run { target c++17 } }

int state;

struct F
{
  int operator() (int) const
  {
    if (state != 2)
      __builtin_abort ();
    return 0;
  }
};

F
make_f ()
{
  if (state != 0)
    __builtin_abort ();
  state = 1;
  return F ();
}

int
arg ()
{
  if (state != 1)
    __builtin_abort ();
  state = 2;
  return 0;
}

int
main ()
{
  make_f () (arg ());
  if (state != 2)
    __builtin_abort ();
}
