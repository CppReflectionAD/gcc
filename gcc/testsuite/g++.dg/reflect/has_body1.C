// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// Test std::meta::has_body.

#include <meta>

using namespace std::meta;

constexpr int defined_fn() {
  return 42;
}

void empty_fn() {}

void declared_only_fn();

void deleted_fn() = delete;

template <typename T>
constexpr T defined_tmpl(T x) {
  return x + 1;
}

template <typename T>
T declared_only_tmpl(T x);

struct S {
  S() = default;
  ~S() = default;
  int mem_defined() const { return 1; }
  int mem_declared() const;
  int mem_deleted() const = delete;
  int field = 0;
};

int global_var = 0;

// Functions with bodies
static_assert(has_body(^^defined_fn));
static_assert(has_body(^^empty_fn));
static_assert(has_body(^^defined_tmpl<int>));
static_assert(has_body(^^S::mem_defined));

// Functions without bodies
static_assert(!has_body(^^declared_only_fn));
static_assert(!has_body(^^deleted_fn));
static_assert(!has_body(^^declared_only_tmpl<int>));
static_assert(!has_body(^^S::mem_declared));
static_assert(!has_body(^^S::mem_deleted));

consteval bool test_defaulted_members() {
  for (info m : members_of(^^S, access_context::current())) {
    if (is_defaulted(m) && has_body(m))
      return false;
  }
  return true;
}
static_assert(test_defaulted_members());

// Non-function reflections return false (do not throw)
static_assert(!has_body(^^int));
static_assert(!has_body(^^S));
static_assert(!has_body(^^S::field));
static_assert(!has_body(^^global_var));
static_assert(!has_body(^^defined_tmpl));
static_assert(!has_body(info{}));
