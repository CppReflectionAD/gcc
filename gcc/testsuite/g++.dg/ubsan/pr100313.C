// PR c++/100313
// { dg-do compile { target c++17 } }
// { dg-options "-fsanitize=null" }

template<auto A = nullptr>
struct Prop {
  void notify()
  {
    if constexpr (A != nullptr) { }
  }
};

struct S {
  inline void fn() { }
};

inline int add (int a, int b) { return a + b; }

template<auto F>
constexpr bool non_null = F != nullptr;

int main()
{
  Prop<&S::fn> prop;
  prop.notify();
  Prop<&add> prop2;
  prop2.notify();
  static_assert (non_null<&add>);
}
