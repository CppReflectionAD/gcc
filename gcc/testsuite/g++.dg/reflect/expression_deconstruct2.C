// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }

#include <meta>
#include <vector>
#include <string_view>

using namespace std::meta;

constexpr float exp(float x) {
  return 1.0f + x;
}

constexpr float sigmoid(float x) {
  return 1.0f + (exp(-x) + 1.0f);
}

struct fixed_string {
  char data[128]{};
  
  constexpr fixed_string() = default;
  constexpr fixed_string(std::string_view sv) {
    size_t len = sv.size() < 127 ? sv.size() : 127;
    for (size_t i = 0; i < len; ++i) {
      data[i] = sv[i];
    }
    data[len] = '\0';
  }

  constexpr bool operator==(std::string_view sv) const {
    std::string_view self(data);
    return self == sv;
  }
};

consteval void collect_all_expressions(info node, std::vector<fixed_string>& res) {
  if (is_expression(node)) {
    res.push_back(fixed_string(display_string_of(node)));
    if (!is_variable(node) && !is_literal(node)) {
      for (info op : operands_of(node)) {
        collect_all_expressions(op, res);
      }
    }
    return;
  }
  if (is_return_statement(node)) {
    collect_all_expressions(return_operand_of(node), res);
    return;
  }
  if (is_statement(node)) {
    for (info child : statements_of(node)) {
      if (child != node) {
        collect_all_expressions(child, res);
      }
    }
  }
}

consteval bool run_test() {
  constexpr info body = body_of( ^^sigmoid );
  std::vector<fixed_string> res;
  collect_all_expressions(body, res);

  if (res.size() != 8) return false;
  if (res[0] != "<plus_expr>") return false;
  if (res[1] != "<plus_expr>") return false;
  if (res[2] != "<call_expr>") return false;
  if (res[3] != "<negate_expr>") return false;
  if (res[4] != "<non_lvalue_expr>") return false;
  if (res[5] != "x") return false;
  if (res[6] != "1.0e+0f") return false;
  if (res[7] != "1.0e+0f") return false;

  return true;
}

static_assert(run_test());
