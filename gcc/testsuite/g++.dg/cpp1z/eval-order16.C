// { dg-do run { target c++17 } }

int order[4];
int idx = 0;

int record (int id)
{
  order[idx++] = id;
  return id;
}

struct F
{
  int operator() (int a, int b) const
  {
    return a + b;
  }
};

F make_f ()
{
  record (1);
  return F ();
}

void normal_fn (int a, int b)
{
}

struct VBase
{
  virtual int operator() (int a, int b) const = 0;
};

struct VDerived : VBase
{
  int operator() (int a, int b) const override
  {
    return a + b;
  }
};

VDerived v_derived;

const VBase &get_v ()
{
  record (1);
  return v_derived;
}

int main ()
{
  // 1. Functor call: object must evaluate before arguments.
  idx = 0;
  make_f () (record (2), record (3));
  if (order[0] != 1)
    __builtin_abort ();

  // The relative order of arguments 2 and 3 should match a normal function call.
  int arg_first = order[1];
  int arg_second = order[2];

  idx = 0;
  normal_fn (record (2), record (3));
  if (order[0] != arg_first || order[1] != arg_second)
    __builtin_abort ();

  // 2. Virtual operator(): object must evaluate before arguments.
  idx = 0;
  get_v () (record (2), record (3));
  if (order[0] != 1)
    __builtin_abort ();
  if (order[1] != arg_first || order[2] != arg_second)
    __builtin_abort ();

  return 0;
}
