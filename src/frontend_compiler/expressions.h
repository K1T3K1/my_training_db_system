#ifndef EXPRESSIONS_H_
#define EXPRESSIONS_H_

#include <memory>
#include <vector>

struct expression : std::enable_shared_from_this<expression> {
  std::shared_ptr<expression> parent_expr = nullptr;
  inline bool has_parent_expr() { return parent_expr != nullptr; }

  std::vector <std::unique_ptr<expression>> children_expr;

};

struct select_expr : public expression {
  std::unique_ptr<from_expr> from_expr_ptr = nullptr;
  inline bool has_from_expr() { return from_expr_ptr != nullptr; }
};

struct from_expr : public expression {};

struct where_expr : public expression {};

struct join_expr : public expression {};

#endif