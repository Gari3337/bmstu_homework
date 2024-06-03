// Copyright 2023 <fleurs>

#include <gtest/gtest.h>
#include "hw_5_optional.h"

class M {
 public:
  M() noexcept {
    ++default_constr;
  }

  M(const M &other) noexcept {
    other.update();
    ++copy_constr;
  }

  M(M &&other) noexcept {
    std::move(other).update();
    ++move_constr;
  }

  M &operator=(const M &other) noexcept {
    if (this != &other) {
      other.update();
      ++copy_assign;
    }
    return *this;
  }

  M &operator=(M &&other) noexcept {
    if (this != &other) {
      std::move(other).update();
      ++move_assign;
    }
    return *this;
  }

  ~M() {
    ++destruct;
  }

  void update() &{  // NOLINT
    ++lvalue_call_count;
  }

  void update() const &{  // NOLINT
    ++const_lvalue_call_count;
  }

  void update() &&{  // NOLINT
    ++rvalue_call_count;
  }

  static size_t instance_count() {
    return default_constr + copy_constr + move_constr - destruct;
  }

  static void reset() {
    default_constr = 0;
    copy_constr = 0;
    move_constr = 0;
    copy_assign = 0;
    move_assign = 0;
    destruct = 0;
    lvalue_call_count = 0;
    const_lvalue_call_count = 0;
    rvalue_call_count = 0;
  }

  inline static size_t default_constr = 0;
  inline static size_t copy_constr = 0;
  inline static size_t move_constr = 0;
  inline static size_t copy_assign = 0;
  inline static size_t move_assign = 0;
  inline static size_t destruct = 0;
  inline static size_t lvalue_call_count = 0;
  inline static size_t const_lvalue_call_count = 0;
  inline static size_t rvalue_call_count = 0;
};

TEST(OptionalTest, HasValueTest) {
  bmstu::optional<int> opt;
  ASSERT_FALSE(opt.has_value());
  bmstu::optional<int> opt2(3);
  ASSERT_TRUE(opt2.has_value());
}

TEST(OptionalTest, CopyValue) {
  bmstu::optional<int> opt_1(123);
  ASSERT_TRUE(opt_1.has_value());
  ASSERT_EQ(opt_1.value(), 123);
  int a = 321;
  bmstu::optional<int> opt_2(a);
  ASSERT_TRUE(opt_2.has_value());
  ASSERT_EQ(opt_2.value(), a);
}

TEST(OptionalTest, MoveValue) {
  int a = 321;
  bmstu::optional<int> opt(std::move(a));
  ASSERT_TRUE(opt.has_value());
  ASSERT_EQ(opt.value(), 321);
}

TEST(OptionalTest, CopyOptional) {
  bmstu::optional<int> opt_1;
  bmstu::optional<int> opt_2(opt_1);
  ASSERT_FALSE(opt_1.has_value());
  ASSERT_FALSE(opt_2.has_value());
}

TEST(OptionalTest, CopyOptionalWithValue) {
  bmstu::optional<int> opt_1(123);
  bmstu::optional<int> opt_2(opt_1);
  ASSERT_TRUE(opt_1.has_value());
  ASSERT_TRUE(opt_2.has_value());
  ASSERT_EQ(opt_2.value(), 123);
}

TEST(OptionalTest, MoveEmptyOptional) {
  bmstu::optional<int> opt_1;
  bmstu::optional<int> opt_2(std::move(opt_1));
  ASSERT_FALSE(opt_1.has_value());
  ASSERT_FALSE(opt_2.has_value());
}

TEST(OptionalTest, MoveOptionalWithValue) {
  bmstu::optional<int> opt_1(123);
  bmstu::optional<int> opt_2(opt_1);
  ASSERT_TRUE(opt_1.has_value());
  ASSERT_TRUE(opt_2.has_value());
  ASSERT_EQ(opt_2.value(), 123);
}

TEST(OptionalTest, ChangeOptionalValue) {
  bmstu::optional<int> opt;
  opt = 123;
  ASSERT_TRUE(opt.has_value());
  ASSERT_EQ(opt.value(), 123);
  opt = 321;
  ASSERT_TRUE(opt.has_value());
  ASSERT_EQ(opt.value(), 321);
}

TEST(OptionalTest, MoveOptionalValue) {
  bmstu::optional<int> opt;
  int a = 123;
  int b = 321;
  opt = std::move(a);
  ASSERT_TRUE(opt.has_value());
  ASSERT_EQ(opt.value(), 123);
  opt = std::move(b);
  ASSERT_TRUE(opt.has_value());
  ASSERT_EQ(opt.value(), 321);
}

TEST(OptionalTest, DefaultM) {
  M::reset();
  ASSERT_EQ(M::instance_count(), 0);
  {
    bmstu::optional<M> opt;
    ASSERT_FALSE(opt.has_value());
    ASSERT_EQ(M::instance_count(), 0);
    ASSERT_EQ(M::default_constr, 0);
    ASSERT_EQ(M::copy_constr, 0);
    ASSERT_EQ(M::move_constr, 0);
    ASSERT_EQ(M::copy_assign, 0);
    ASSERT_EQ(M::move_assign, 0);
    ASSERT_EQ(M::destruct, 0);
    ASSERT_EQ(M::lvalue_call_count, 0);
    ASSERT_EQ(M::const_lvalue_call_count, 0);
    ASSERT_EQ(M::rvalue_call_count, 0);
  }
}

TEST(OptionalTest, CopyValueM) {
  M::reset();
  ASSERT_EQ(M::instance_count(), 0);
  {
    M variable;
    bmstu::optional<M> opt(variable);
    ASSERT_TRUE(opt.has_value());
    ASSERT_EQ(M::instance_count(), 2);
    ASSERT_EQ(M::default_constr, 1);
    ASSERT_EQ(M::copy_constr, 1);
    ASSERT_EQ(M::move_constr, 0);
    ASSERT_EQ(M::copy_assign, 0);
    ASSERT_EQ(M::move_assign, 0);
    ASSERT_EQ(M::destruct, 0);
    ASSERT_EQ(M::lvalue_call_count, 0);
    ASSERT_EQ(M::const_lvalue_call_count, 1);
    ASSERT_EQ(M::rvalue_call_count, 0);
  }
  ASSERT_EQ(M::default_constr, 1);
  ASSERT_EQ(M::copy_constr, 1);
  ASSERT_EQ(M::destruct, 2);
  ASSERT_EQ(M::instance_count(), 0);
}

TEST(OptionalTest, CopyOperatorValueM) {
  M::reset();
  ASSERT_EQ(M::instance_count(), 0);
  {
    M variable;
    bmstu::optional<M> opt;
    opt = variable;
    ASSERT_TRUE(opt.has_value());
    ASSERT_EQ(M::instance_count(), 2);
    ASSERT_EQ(M::default_constr, 1);
    ASSERT_EQ(M::copy_constr, 1);
    ASSERT_EQ(M::move_constr, 0);
    ASSERT_EQ(M::copy_assign, 0);
    ASSERT_EQ(M::move_assign, 0);
    ASSERT_EQ(M::destruct, 0);
    ASSERT_EQ(M::lvalue_call_count, 0);
    ASSERT_EQ(M::const_lvalue_call_count, 1);
    ASSERT_EQ(M::rvalue_call_count, 0);
  }
  ASSERT_EQ(M::default_constr, 1);
  ASSERT_EQ(M::copy_constr, 1);
  ASSERT_EQ(M::destruct, 2);
  ASSERT_EQ(M::instance_count(), 0);
}

TEST(OptionalTest, CopyOperatorFromOneToAnotherM) {
  M::reset();
  ASSERT_EQ(M::instance_count(), 0);
  {
    M variable_1;
    M variable_2;
    bmstu::optional<M> opt(variable_1);
    opt = variable_2;
    ASSERT_TRUE(opt.has_value());
    ASSERT_EQ(M::instance_count(), 3);
    ASSERT_EQ(M::default_constr, 2);
    ASSERT_EQ(M::copy_constr, 1);
    ASSERT_EQ(M::move_constr, 0);
    ASSERT_EQ(M::copy_assign, 1);
    ASSERT_EQ(M::move_assign, 0);
    ASSERT_EQ(M::destruct, 0);
    ASSERT_EQ(M::lvalue_call_count, 0);
    ASSERT_EQ(M::const_lvalue_call_count, 2);
    ASSERT_EQ(M::rvalue_call_count, 0);
  }
  ASSERT_EQ(M::default_constr, 2);
  ASSERT_EQ(M::copy_constr, 1);
  ASSERT_EQ(M::copy_assign, 1);
  ASSERT_EQ(M::destruct, 3);
  ASSERT_EQ(M::instance_count(), 0);
}

TEST(OptionalTest, MoveValueM) {
  M::reset();
  ASSERT_EQ(M::instance_count(), 0);
  {
    M variable;
    bmstu::optional<M> opt(std::move(variable));
    ASSERT_TRUE(opt.has_value());
    ASSERT_EQ(M::instance_count(), 2);
    ASSERT_EQ(M::default_constr, 1);
    ASSERT_EQ(M::copy_constr, 0);
    ASSERT_EQ(M::move_constr, 1);
    ASSERT_EQ(M::copy_assign, 0);
    ASSERT_EQ(M::move_assign, 0);
    ASSERT_EQ(M::destruct, 0);
    ASSERT_EQ(M::lvalue_call_count, 0);
    ASSERT_EQ(M::const_lvalue_call_count, 0);
    ASSERT_EQ(M::rvalue_call_count, 1);
  }
  ASSERT_EQ(M::default_constr, 1);
  ASSERT_EQ(M::move_constr, 1);
  ASSERT_EQ(M::destruct, 2);
  ASSERT_EQ(M::instance_count(), 0);
}

TEST(OptionalTest, MoveOperatorValueM) {
  M::reset();
  ASSERT_EQ(M::instance_count(), 0);
  {
    M variable;
    bmstu::optional<M> opt;
    opt = std::move(variable);
    ASSERT_TRUE(opt.has_value());
    ASSERT_EQ(M::instance_count(), 2);
    ASSERT_EQ(M::default_constr, 1);
    ASSERT_EQ(M::copy_constr, 0);
    ASSERT_EQ(M::move_constr, 1);
    ASSERT_EQ(M::copy_assign, 0);
    ASSERT_EQ(M::move_assign, 0);
    ASSERT_EQ(M::destruct, 0);
    ASSERT_EQ(M::lvalue_call_count, 0);
    ASSERT_EQ(M::const_lvalue_call_count, 0);
    ASSERT_EQ(M::rvalue_call_count, 1);
  }
  ASSERT_EQ(M::default_constr, 1);
  ASSERT_EQ(M::move_constr, 1);
  ASSERT_EQ(M::destruct, 2);
  ASSERT_EQ(M::instance_count(), 0);
}

TEST(OptionalTest, MoveOperatorFromOneToAnotherM) {
  M::reset();
  ASSERT_EQ(M::instance_count(), 0);
  {
    M variable_1;
    M variable_2;
    bmstu::optional<M> opt(variable_1);
    opt = std::move(variable_2);
    ASSERT_TRUE(opt.has_value());
    ASSERT_EQ(M::instance_count(), 3);
    ASSERT_EQ(M::default_constr, 2);
    ASSERT_EQ(M::copy_constr, 1);
    ASSERT_EQ(M::move_constr, 0);
    ASSERT_EQ(M::copy_assign, 0);
    ASSERT_EQ(M::move_assign, 1);
    ASSERT_EQ(M::destruct, 0);
    ASSERT_EQ(M::lvalue_call_count, 0);
    ASSERT_EQ(M::const_lvalue_call_count, 1);
    ASSERT_EQ(M::rvalue_call_count, 1);
  }
  ASSERT_EQ(M::default_constr, 2);
  ASSERT_EQ(M::copy_constr, 1);
  ASSERT_EQ(M::move_assign, 1);
  ASSERT_EQ(M::destruct, 3);
  ASSERT_EQ(M::instance_count(), 0);
}

TEST(OptionalTest, CopyEmptyOptionalM) {
  M::reset();
  ASSERT_EQ(M::instance_count(), 0);
  {
    bmstu::optional<M> opt_1;
    bmstu::optional<M> opt_2(opt_1);
    ASSERT_FALSE(opt_1.has_value());
    ASSERT_FALSE(opt_2.has_value());
    ASSERT_EQ(M::instance_count(), 0);
    ASSERT_EQ(M::default_constr, 0);
    ASSERT_EQ(M::copy_constr, 0);
    ASSERT_EQ(M::move_constr, 0);
    ASSERT_EQ(M::copy_assign, 0);
    ASSERT_EQ(M::move_assign, 0);
    ASSERT_EQ(M::destruct, 0);
    ASSERT_EQ(M::lvalue_call_count, 0);
    ASSERT_EQ(M::const_lvalue_call_count, 0);
    ASSERT_EQ(M::rvalue_call_count, 0);
  }
}

TEST(OptionalTest, CopyOptionalWithValueM) {
  M::reset();
  ASSERT_EQ(M::instance_count(), 0);
  {
    M variable;
    bmstu::optional<M> opt_1(variable);
    bmstu::optional<M> opt_2(opt_1);
    ASSERT_TRUE(opt_1.has_value());
    ASSERT_TRUE(opt_2.has_value());
    ASSERT_EQ(M::instance_count(), 3);
    ASSERT_EQ(M::default_constr, 1);
    ASSERT_EQ(M::copy_constr, 2);
    ASSERT_EQ(M::move_constr, 0);
    ASSERT_EQ(M::copy_assign, 0);
    ASSERT_EQ(M::move_assign, 0);
    ASSERT_EQ(M::destruct, 0);
    ASSERT_EQ(M::lvalue_call_count, 0);
    ASSERT_EQ(M::const_lvalue_call_count, 2);
    ASSERT_EQ(M::rvalue_call_count, 0);
  }
  ASSERT_EQ(M::default_constr, 1);
  ASSERT_EQ(M::copy_constr, 2);
  ASSERT_EQ(M::destruct, 3);
  ASSERT_EQ(M::instance_count(), 0);
}

TEST(OptionalTest, MoveEmptyOptionalM) {
  M::reset();
  ASSERT_EQ(M::instance_count(), 0);
  {
    bmstu::optional<M> opt_1;
    bmstu::optional<M> opt_2(std::move(opt_1));
    ASSERT_FALSE(opt_1.has_value());
    ASSERT_FALSE(opt_2.has_value());
    ASSERT_EQ(M::instance_count(), 0);
    ASSERT_EQ(M::default_constr, 0);
    ASSERT_EQ(M::copy_constr, 0);
    ASSERT_EQ(M::move_constr, 0);
    ASSERT_EQ(M::copy_assign, 0);
    ASSERT_EQ(M::move_assign, 0);
    ASSERT_EQ(M::destruct, 0);
    ASSERT_EQ(M::lvalue_call_count, 0);
    ASSERT_EQ(M::const_lvalue_call_count, 0);
    ASSERT_EQ(M::rvalue_call_count, 0);
  }
}

TEST(OptionalTest, MoveOptionalWithValueM) {
  M::reset();
  ASSERT_EQ(M::instance_count(), 0);
  {
    M variable;
    bmstu::optional<M> opt_1(variable);
    bmstu::optional<M> opt_2(std::move(opt_1));
    ASSERT_TRUE(opt_2.has_value());
    ASSERT_EQ(M::instance_count(), 3);
    ASSERT_EQ(M::default_constr, 1);
    ASSERT_EQ(M::copy_constr, 1);
    ASSERT_EQ(M::move_constr, 1);
    ASSERT_EQ(M::copy_assign, 0);
    ASSERT_EQ(M::move_assign, 0);
    ASSERT_EQ(M::destruct, 0);
    ASSERT_EQ(M::lvalue_call_count, 0);
    ASSERT_EQ(M::const_lvalue_call_count, 1);
    ASSERT_EQ(M::rvalue_call_count, 1);
  }
  ASSERT_EQ(M::default_constr, 1);
  ASSERT_EQ(M::copy_constr, 1);
  ASSERT_EQ(M::move_constr, 1);
  ASSERT_EQ(M::destruct, 3);
  ASSERT_EQ(M::instance_count(), 0);
}

TEST(OptionalTest, CopyOptionalFromValueToAnotherValueOperatorM) {
  M::reset();
  ASSERT_EQ(M::instance_count(), 0);
  {
    M variable_1;
    M variable_2;
    bmstu::optional<M> opt_1(variable_1);
    bmstu::optional<M> opt_2(variable_2);
    opt_2 = opt_1;
    ASSERT_TRUE(opt_1.has_value());
    ASSERT_TRUE(opt_2.has_value());
    ASSERT_EQ(M::instance_count(), 4);
    ASSERT_EQ(M::default_constr, 2);
    ASSERT_EQ(M::copy_constr, 2);
    ASSERT_EQ(M::move_constr, 0);
    ASSERT_EQ(M::copy_assign, 1);
    ASSERT_EQ(M::move_assign, 0);
    ASSERT_EQ(M::destruct, 0);
    ASSERT_EQ(M::lvalue_call_count, 0);
    ASSERT_EQ(M::const_lvalue_call_count, 3);
    ASSERT_EQ(M::rvalue_call_count, 0);
  }
  ASSERT_EQ(M::default_constr, 2);
  ASSERT_EQ(M::copy_constr, 2);
  ASSERT_EQ(M::copy_assign, 1);
  ASSERT_EQ(M::destruct, 4);
  ASSERT_EQ(M::instance_count(), 0);
}

TEST(OptionalTest, CopyOptionalFromEmptyToValueOperatorM) {
  M::reset();
  ASSERT_EQ(M::instance_count(), 0);
  {
    M variable_1;
    bmstu::optional<M> opt_1(variable_1);
    bmstu::optional<M> opt_2;
    opt_2 = opt_1;
    ASSERT_TRUE(opt_1.has_value());
    ASSERT_TRUE(opt_2.has_value());
    ASSERT_EQ(M::instance_count(), 3);
    ASSERT_EQ(M::default_constr, 1);
    ASSERT_EQ(M::copy_constr, 2);
    ASSERT_EQ(M::move_constr, 0);
    ASSERT_EQ(M::copy_assign, 0);
    ASSERT_EQ(M::move_assign, 0);
    ASSERT_EQ(M::destruct, 0);
    ASSERT_EQ(M::lvalue_call_count, 0);
    ASSERT_EQ(M::const_lvalue_call_count, 2);
    ASSERT_EQ(M::rvalue_call_count, 0);
  }
  ASSERT_EQ(M::default_constr, 1);
  ASSERT_EQ(M::copy_constr, 2);
  ASSERT_EQ(M::destruct, 3);
  ASSERT_EQ(M::instance_count(), 0);
}

TEST(OptionalTest, CopyOptionalFromValueToEmptyM) {
  M::reset();
  ASSERT_EQ(M::instance_count(), 0);
  {
    M variable_1;
    bmstu::optional<M> opt_1(variable_1);
    bmstu::optional<M> opt_2;
    opt_1 = opt_2;
    ASSERT_FALSE(opt_1.has_value());
    ASSERT_FALSE(opt_2.has_value());
    ASSERT_EQ(M::instance_count(), 1);
    ASSERT_EQ(M::default_constr, 1);
    ASSERT_EQ(M::copy_constr, 1);
    ASSERT_EQ(M::move_constr, 0);
    ASSERT_EQ(M::copy_assign, 0);
    ASSERT_EQ(M::move_assign, 0);
    ASSERT_EQ(M::destruct, 1);
    ASSERT_EQ(M::lvalue_call_count, 0);
    ASSERT_EQ(M::const_lvalue_call_count, 1);
    ASSERT_EQ(M::rvalue_call_count, 0);
  }
  ASSERT_EQ(M::default_constr, 1);
  ASSERT_EQ(M::copy_constr, 1);
  ASSERT_EQ(M::destruct, 2);
  ASSERT_EQ(M::instance_count(), 0);
}

TEST(OptionalTest, MoveOptionalOperatorM) {
  M::reset();
  ASSERT_EQ(M::instance_count(), 0);
  {
    M variable_1;
    M variable_2;
    bmstu::optional<M> opt_1(variable_1);
    bmstu::optional<M> opt_2(variable_2);
    opt_2 = std::move(opt_1);
    ASSERT_TRUE(opt_2.has_value());
    ASSERT_EQ(M::instance_count(), 4);
    ASSERT_EQ(M::default_constr, 2);
    ASSERT_EQ(M::copy_constr, 2);
    ASSERT_EQ(M::move_constr, 0);
    ASSERT_EQ(M::copy_assign, 0);
    ASSERT_EQ(M::move_assign, 1);
    ASSERT_EQ(M::destruct, 0);
    ASSERT_EQ(M::lvalue_call_count, 0);
    ASSERT_EQ(M::const_lvalue_call_count, 2);
    ASSERT_EQ(M::rvalue_call_count, 1);
  }
  ASSERT_EQ(M::default_constr, 2);
  ASSERT_EQ(M::copy_constr, 2);
  ASSERT_EQ(M::move_assign, 1);
  ASSERT_EQ(M::destruct, 4);
  ASSERT_EQ(M::instance_count(), 0);
}

TEST(OptionalTest, MoveOptionalFromEmptyToValueOperatorM) {
  M::reset();
  ASSERT_EQ(M::instance_count(), 0);
  {
    M variable_1;
    bmstu::optional<M> opt_1(variable_1);
    bmstu::optional<M> opt_2;
    opt_2 = std::move(opt_1);
    ASSERT_TRUE(opt_2.has_value());
    ASSERT_EQ(M::instance_count(), 3);
    ASSERT_EQ(M::default_constr, 1);
    ASSERT_EQ(M::copy_constr, 1);
    ASSERT_EQ(M::move_constr, 1);
    ASSERT_EQ(M::copy_assign, 0);
    ASSERT_EQ(M::move_assign, 0);
    ASSERT_EQ(M::destruct, 0);
    ASSERT_EQ(M::lvalue_call_count, 0);
    ASSERT_EQ(M::const_lvalue_call_count, 1);
    ASSERT_EQ(M::rvalue_call_count, 1);
  }
  ASSERT_EQ(M::default_constr, 1);
  ASSERT_EQ(M::copy_constr, 1);
  ASSERT_EQ(M::destruct, 3);
  ASSERT_EQ(M::instance_count(), 0);
}

TEST(OptionalTest, MoveOptionalOperatorFromValueToEmptyM) {
  M::reset();
  ASSERT_EQ(M::instance_count(), 0);
  {
    M variable_1;
    bmstu::optional<M> opt_1(variable_1);
    bmstu::optional<M> opt_2;
    opt_1 = std::move(opt_2);
    ASSERT_FALSE(opt_1.has_value());
    ASSERT_FALSE(opt_2.has_value());
    ASSERT_EQ(M::instance_count(), 1);
    ASSERT_EQ(M::default_constr, 1);
    ASSERT_EQ(M::copy_constr, 1);
    ASSERT_EQ(M::move_constr, 0);
    ASSERT_EQ(M::copy_assign, 0);
    ASSERT_EQ(M::move_assign, 0);
    ASSERT_EQ(M::destruct, 1);
    ASSERT_EQ(M::lvalue_call_count, 0);
    ASSERT_EQ(M::const_lvalue_call_count, 1);
    ASSERT_EQ(M::rvalue_call_count, 0);
  }
  ASSERT_EQ(M::default_constr, 1);
  ASSERT_EQ(M::copy_constr, 1);
  ASSERT_EQ(M::destruct, 2);
  ASSERT_EQ(M::instance_count(), 0);
}

TEST(OptionalTest, ThrowBadOptionalAccess) {
  bmstu::optional<M> opt;
  ASSERT_FALSE(opt.has_value());
  ASSERT_THROW(opt.value(), bmstu::bad_optional_access);
  ASSERT_THROW(std::move(opt).value(), bmstu::bad_optional_access);

  const bmstu::optional<M> opt_const{};
  ASSERT_FALSE(opt_const.has_value());
//  ASSERT_THROW(opt_const.value(), bmstu::bad_optional_access);
//  ASSERT_THROW(std::move(opt_const).value(),
//               bmstu::bad_optional_access);  // NO EFFECT move
}
