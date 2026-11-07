// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection -O2 -fdump-tree-gimple" }
// The blocks that -freflection keeps don't change which loops count as
// trivially empty: each of these is annotated as without the option, and
// the last two aren't.
// { dg-final { scan-tree-dump-times ".ANNOTATE \\\(\[^\n\r]*, 5, 0\\\)" 7 "gimple" } }

constexpr bool yes () { return true; }
void g ();
int v;

void
f (int i)
{
  switch (i)
    {
    case 0: while (yes ()) { { } } break;
    case 1: while (yes ()) { { } { } } break;
    case 2: while (yes ()) { { { } } } break;
    case 3: while (yes ()) { { ; } { } } break;
    case 4: do { { } } while (yes ()); break;
    case 5: for (v = 0; yes (); ) { { } } break;
    case 6: while (yes ()) { { g (); } } break;
    case 7: while (yes ()) { { int a = 0; } } break;
    }
}

template <class T>
void
t (int i)
{
  while (yes ()) { { } }
}

template void t<int> (int);
