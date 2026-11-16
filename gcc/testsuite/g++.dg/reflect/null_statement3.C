// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection -O2 -fdump-tree-gimple" }
// The statements that a null statement adds under -freflection don't change
// which loops count as trivially empty: each of these is annotated as without
// the option, and the last two aren't.
// { dg-final { scan-tree-dump-times ".ANNOTATE \\\(\[^\n\r]*, 5, 0\\\)" 11 "gimple" } }

constexpr bool yes () { return true; }
void g ();
int v;

void
f (int i)
{
  switch (i)
    {
    case 0: while (yes ()) ; break;
    case 1: while (yes ()) { } break;
    case 2: while (yes ()) { ; } break;
    case 3: while (yes ()) { ; ; } break;
    case 4: while (yes ()) { { ; } } break;
    case 5: do ; while (yes ()); break;
    case 6: do { ; } while (yes ()); break;
    case 7: for (v = 0; yes (); ) ; break;
    case 8: for (v = 0; yes (); ) { ; } break;
    case 9: while (yes ()) { ; g (); } break;
    case 10: while (yes ()) { g (); ; } break;
    }
}

template <class T>
void
t (int i)
{
  if (i)
    while (yes ()) ;
  else
    while (yes ()) { ; }
}

template void t<int> (int);
