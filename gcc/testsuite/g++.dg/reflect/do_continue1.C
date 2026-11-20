// { dg-do run }
// A `continue' targeting `do { ... } while (0)' (including from a nested
// `switch') reaches the condition and exits the loop, so a following `break'
// is reachable and must not be dropped by finish_break_stmt.

#define NI __attribute__((noipa))

NI int
do_continue (int s, int x)
{
  switch (s)
    {
    case 0:
      do { if (x) continue; return 1; } while (0);
      break;
    case 1:
      return 2;
    }
  return 3;
}

NI int
loop_continue (int x)
{
  int n = 0;
  for (int i = 0; i < 3; ++i)
    {
      ++n;
      do { if (x) continue; return 100; } while (0);
      break;
    }
  return n;
}

NI int
do_switch_continue (int s, int x)
{
  switch (s)
    {
    case 0:
      do
	{
	  switch (x)
	    {
	    case 1: continue;
	    default: return 1;
	    }
	}
      while (0);
      break;
    case 1:
      return 2;
    }
  return 3;
}

int
main ()
{
  if (do_continue (0, 1) != 3
      || do_continue (0, 0) != 1
      || loop_continue (1) != 1
      || do_switch_continue (0, 1) != 3
      || do_switch_continue (0, 0) != 1)
    __builtin_abort ();
}
