// Copyright 2023 <fleurs>

#include <gtest/gtest.h>

#include <iostream>
#include <set>

#include "hw_4_list.h"

TEST(ListTest, 1DefaultListTest) {
  bmstu::list<int> my_list;
  ASSERT_EQ(my_list.size(), 0);
  ASSERT_TRUE(my_list.empty());
}

TEST(ListTest, 1PushBackAndSize) {
  bmstu::list<int> my_list = {};
  my_list.push_back(42);
  ASSERT_EQ(my_list.size(), 1);
  ASSERT_FALSE(my_list.empty());
}

TEST(ListTest1, 1PushFrontAndSize) {
  bmstu::list<int> my_list;
  my_list.push_front(42);
  ASSERT_EQ(my_list.size(), 1);
  ASSERT_FALSE(my_list.empty());
}

TEST(ListTest, 1Clear) {
  bmstu::list<int> my_list;
  my_list.push_back(42);
  my_list.clear();
  ASSERT_EQ(my_list.size(), 0);
  ASSERT_TRUE(my_list.empty());
}

TEST(ListTest, 1Iterators) {
  bmstu::list<int> my_list;
  my_list.push_back(1);
  my_list.push_back(2);
  my_list.push_back(3);

  auto it = my_list.begin();
  ASSERT_EQ(*it, 1);

  ++it;
  ASSERT_EQ(*it, 2);

  it++;
  ASSERT_EQ(*it, 3);
}

TEST(ListTest, 1CopyListTest) {
  bmstu::list<int> original;
  original.push_back(42);

  bmstu::list<int> copy(original);
  ASSERT_EQ(copy.size(), 1);
  ASSERT_EQ(copy[0], 42);
}

TEST(ListTest, DefaultListTest) {
  bmstu::list<int> my_list;
  ASSERT_EQ(my_list.size(), 0);
  ASSERT_TRUE(my_list.empty());
}

TEST(ListTest, PushBackAndSize) {
  bmstu::list<int> my_list;
  my_list.push_back(42);
  ASSERT_EQ(my_list.size(), 1);
  ASSERT_FALSE(my_list.empty());
}

TEST(ListTest, PushFrontAndSize) {
  bmstu::list<int> my_list;
  my_list.push_front(42);
  ASSERT_EQ(my_list.size(), 1);
  ASSERT_FALSE(my_list.empty());
}

TEST(ListTest, Clear) {
  bmstu::list<int> my_list;
  my_list.push_back(42);
  my_list.clear();
  ASSERT_EQ(my_list.size(), 0);
  ASSERT_TRUE(my_list.empty());
}

TEST(ListTest, Iterators) {
  bmstu::list<int> my_list;
  my_list.push_back(1);
  my_list.push_back(2);
  my_list.push_back(3);

  auto it = my_list.begin();
  ASSERT_EQ(*it, 1);

  ++it;
  ASSERT_EQ(*it, 2);

  it++;
  ASSERT_EQ(*it, 3);
}

TEST(ListTest, CopyListTest) {
  bmstu::list<int> original;
  original.push_back(42);

  bmstu::list<int> copy(original);
  ASSERT_EQ(copy.size(), 1);
  ASSERT_EQ(copy[0], 42);
}

TEST(ListTest, MoveListTest) {
  bmstu::list<int> original;
  original.push_back(42);

  bmstu::list<int> moved(std::move(original));
  ASSERT_EQ(moved.size(), 1);
  ASSERT_EQ(moved[0], 42);
  ASSERT_EQ(original.size(), 0);
  ASSERT_TRUE(original.empty());
}

TEST(ListTest, CopyAssignment) {
  bmstu::list<int> original;
  original.push_back(42);

  bmstu::list<int> copy;
  copy = original;
  ASSERT_EQ(copy.size(), 1);
  ASSERT_EQ(copy[0], 42);
}

TEST(ListTest, MoveAssignment) {
  bmstu::list<int> original;
  original.push_back(42);

  bmstu::list<int> moved;
  moved = std::move(original);
  ASSERT_EQ(moved.size(), 1);
  ASSERT_EQ(moved[0], 42);
  ASSERT_EQ(original.size(), 0);
  ASSERT_TRUE(original.empty());
}

TEST(ListTest, Swap) {
  bmstu::list<int> list1;
  list1.push_back(1);
  list1.push_back(2);

  bmstu::list<int> list2;
  list2.push_back(3);
  list2.push_back(4);

  list1.swap(list2);

  ASSERT_EQ(list1.size(), 2);
  ASSERT_EQ(list1[0], 3);
  ASSERT_EQ(list1[1], 4);

  ASSERT_EQ(list2.size(), 2);
  ASSERT_EQ(list2[0], 1);
  ASSERT_EQ(list2[1], 2);
}

TEST(ListTest, Equality) {
  bmstu::list<int> list1;
  list1.push_back(1);
  list1.push_back(2);

  bmstu::list<int> list2;
  list2.push_back(1);
  list2.push_back(2);

  ASSERT_TRUE(list1 == list2);

  list2.push_back(3);
  ASSERT_FALSE(list1 == list2);
}

TEST(ListTest, Inequality) {
  bmstu::list<int> list1;
  list1.push_back(1);
  list1.push_back(2);

  bmstu::list<int> list2;
  list2.push_back(1);
  list2.push_back(2);

  ASSERT_FALSE(list1 != list2);

  list2.push_back(3);
  ASSERT_TRUE(list1 != list2);
}

TEST(ListTest, LessThan) {
  bmstu::list<int> list1;
  list1.push_back(1);
  list1.push_back(2);

  bmstu::list<int> list2;
  list2.push_back(1);
  list2.push_back(2);
  list2.push_back(3);

  ASSERT_TRUE(list1 < list2);
}

TEST(ListTest, GreaterThan) {
  bmstu::list<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  bmstu::list<int> list2;
  list2.push_back(1);
  list2.push_back(2);

  ASSERT_TRUE(list1 > list2);
}

TEST(ListTest, InsertTest) {
  // Создаем список
  bmstu::list<int> my_list;

  // Вставляем элементы в список
  my_list.push_back(1);
  my_list.push_back(2);
  my_list.push_back(3);

  // Вставляем элемент в середину списка
  auto it = my_list.begin();
  ++it;
  my_list.insert(it, 10);

  // Проверяем, что элементы вставлены верно
  EXPECT_EQ(my_list.size(), 4);
  EXPECT_EQ(my_list[0], 1);
  EXPECT_EQ(my_list[1], 10);
  EXPECT_EQ(my_list[2], 2);
  EXPECT_EQ(my_list[3], 3);
}

TEST(ListTest, InitializerListTest) {
  // Инициализируем список с использованием initializer list
  bmstu::list<int> my_list = {1, 2, 3, 4, 5};

  // Проверяем, что элементы в списке соответствуют ожидаемым значениям
  EXPECT_EQ(my_list.size(), 5);
  EXPECT_EQ(my_list[0], 1);
  EXPECT_EQ(my_list[1], 2);
  EXPECT_EQ(my_list[2], 3);
  EXPECT_EQ(my_list[3], 4);
  EXPECT_EQ(my_list[4], 5);
}

TEST(ListTest, OutputListTestTest) {
  // Инициализируем список
  bmstu::list<int> my_list = {1, 2, 3, 4, 5};

  // Подготавливаем поток для вывода
  std::ostringstream oss;

  // Используем оператор вывода для записи списка в поток
  oss << my_list;

  // Проверяем, что результат соответствует ожидаемой строке
  EXPECT_EQ(oss.str(), "[ 1, 2, 3, 4, 5 ]");
}

TEST(ListTest, SubscriptListTestTest) {
  // Инициализируем список
  bmstu::list<int> my_list = {1, 2, 3, 4, 5};

  // Проверяем, что оператор [] возвращает ожидаемые значения
  EXPECT_EQ(my_list[0], 1);
  EXPECT_EQ(my_list[1], 2);
  EXPECT_EQ(my_list[2], 3);
  EXPECT_EQ(my_list[3], 4);
  EXPECT_EQ(my_list[4], 5);
}

TEST(ListTest, Default) {
  bmstu::list<int> my_list;
  auto it_b = my_list.begin();
  auto it_e = my_list.end();

  ASSERT_EQ(my_list.size(), 0);
  ASSERT_TRUE(it_b == it_e);

  --it_b;
  --it_e;
  ASSERT_TRUE(it_b == it_e);
}

TEST(ListTest, IList) {
  bmstu::list<int> my_list({0, 1, 2, 3, 4});
  bmstu::list<int>::iterator it_b = my_list.begin();
  bmstu::list<int>::iterator it_e = my_list.end();

  ASSERT_EQ(my_list.size(), 5);
  for (int a = 0; it_b != it_e; ++it_b, ++a) {
    ASSERT_TRUE(*it_b == a);
    ASSERT_TRUE(my_list[a] == a);
  }

  --it_e;
  it_b = my_list.begin() - 1;
  for (int a = 4; it_b != it_e; --it_e, --a) {
    ASSERT_TRUE(*it_e == a);
    ASSERT_TRUE(my_list[a] == a);
  }
}

TEST(ListTest, Copy) {
  bmstu::list<int> my_list_1({0, 1, 2, 3, 4});
  bmstu::list<int>::iterator it_b_1 = my_list_1.begin();
  bmstu::list<int>::iterator it_e_1 = my_list_1.end();

  bmstu::list<int> my_list_2(my_list_1);
  bmstu::list<int>::iterator it_b_2 = my_list_2.begin();
  bmstu::list<int>::iterator it_e_2 = my_list_2.end();

  ASSERT_EQ(my_list_1.size(), 5);
  ASSERT_EQ(my_list_2.size(), 5);
  for (int a = 0; it_b_2 != it_e_2; ++it_b_1, ++it_b_2, ++a) {
    ASSERT_TRUE(*it_b_1 == a);
    ASSERT_TRUE(*it_b_2 == a);
    ASSERT_TRUE(my_list_1[a] == my_list_2[a]);
  }

  --it_e_1;
  --it_e_2;
  it_b_1 = my_list_1.begin() - 1;
  it_b_2 = my_list_2.begin() - 1;
  for (int a = 4; it_b_2 != it_e_2; --it_e_1, --it_e_2, --a) {
    ASSERT_TRUE(*it_e_1 == a);
    ASSERT_TRUE(*it_e_2 == a);
    ASSERT_TRUE(my_list_1[a] == my_list_2[a]);
  }
}

TEST(ListTest, Move) {
  bmstu::list<int> my_list_1({0, 1, 2, 3, 4});
  bmstu::list<int> my_list_2(std::move(my_list_1));
  bmstu::list<int>::iterator it_b_2 = my_list_2.begin();
  bmstu::list<int>::iterator it_e_2 = my_list_2.end();

  ASSERT_EQ(my_list_1.size(), 0);
  ASSERT_EQ(my_list_2.size(), 5);
  for (int a = 0; it_b_2 != it_e_2; ++it_b_2, ++a) {
    ASSERT_TRUE(*it_b_2 == a);
    ASSERT_TRUE(my_list_2[a] == a);
  }
}

TEST(ListTest, push_back) {
  bmstu::list<int> my_list({0, 1, 2, 3, 4});

  my_list.push_back(5);

  bmstu::list<int>::iterator it_b = my_list.begin();
  bmstu::list<int>::iterator it_e = my_list.end();

  ASSERT_EQ(my_list.size(), 6);
  for (int a = 0; it_b != it_e; ++it_b, ++a) {
    ASSERT_TRUE(*it_b == a);
    ASSERT_TRUE(my_list[a] == a);
  }

  --it_e;
  it_b = my_list.begin() - 1;
  for (int a = 5; it_b != it_e; --it_e, --a) {
    ASSERT_TRUE(*it_e == a);
    ASSERT_TRUE(my_list[a] == a);
  }
}

TEST(ListTest, push_front) {
  bmstu::list<int> my_list({1, 2, 3, 4, 5});

  my_list.push_front(0);

  bmstu::list<int>::iterator it_b = my_list.begin();
  bmstu::list<int>::iterator it_e = my_list.end();

  ASSERT_EQ(my_list.size(), 6);
  for (int a = 0; it_b != it_e; ++it_b, ++a) {
    ASSERT_TRUE(*it_b == a);
    ASSERT_TRUE(my_list[a] == a);
  }

  --it_e;
  it_b = my_list.begin() - 1;
  for (int a = 5; it_b != it_e; --it_e, --a) {
    ASSERT_TRUE(*it_e == a);
    ASSERT_TRUE(my_list[a] == a);
  }
}

TEST(ListTest, clear) {
  bmstu::list<int> my_list({1, 2, 3, 4, 5});

  my_list.clear();

  bmstu::list<int>::iterator it_b = my_list.begin();
  bmstu::list<int>::iterator it_e = my_list.end();

  ASSERT_EQ(my_list.size(), 0);
  ASSERT_TRUE(it_b == it_e);

  --it_b;
  --it_e;
  ASSERT_TRUE(it_b == it_e);
}

TEST(ListTest, swap) {
  bmstu::list<int> my_list_1({0, 1, 2, 3, 4});
  bmstu::list<int> my_list_2({7, 8, 9});

  my_list_1.swap(my_list_2);

  bmstu::list<int>::iterator it_b_1 = my_list_1.begin();
  bmstu::list<int>::iterator it_e_1 = my_list_1.end();
  bmstu::list<int>::iterator it_b_2 = my_list_2.begin();
  bmstu::list<int>::iterator it_e_2 = my_list_2.end();

  ASSERT_EQ(my_list_1.size(), 3);
  ASSERT_EQ(my_list_2.size(), 5);

  for (int a = 7; it_b_1 != it_e_1; ++it_b_1, ++a) {
    ASSERT_TRUE(*it_b_1 == a);
    ASSERT_TRUE(my_list_1[a - 7] == a);
  }

  --it_e_1;
  it_b_1 = my_list_1.begin() - 1;
  for (int a = 9; it_b_1 != it_e_1; --it_e_1, --a) {
    ASSERT_TRUE(*it_e_1 == a);
    ASSERT_TRUE(my_list_1[a - 7] == a);
  }

  for (int a = 0; it_b_2 != it_e_2; ++it_b_2, ++a) {
    ASSERT_TRUE(*it_b_2 == a);
    ASSERT_TRUE(my_list_2[a] == a);
  }

  --it_e_2;
  it_b_2 = my_list_2.begin() - 1;
  for (int a = 4; it_b_2 != it_e_2; --it_e_2, --a) {
    ASSERT_TRUE(*it_e_2 == a);
    ASSERT_TRUE(my_list_2[a] == a);
  }
}

TEST(ListTest, Index) {
  bmstu::list<int> my_list({0, 1, 2, 0, 4});
  my_list[3] = 3;

  ASSERT_EQ(my_list.size(), 5);

  bmstu::list<int>::iterator it_b = my_list.begin();
  bmstu::list<int>::iterator it_e = my_list.end();
  for (int a = 0; it_b != it_e; ++it_b, ++a) {
    ASSERT_TRUE(*it_b == a);
    ASSERT_TRUE(my_list[a] == a);
  }

  --it_e;
  it_b = my_list.begin() - 1;
  for (int a = 4; it_b != it_e; --it_e, --a) {
    ASSERT_TRUE(*it_e == a);
    ASSERT_TRUE(my_list[a] == a);
  }
}

TEST(ListTest, EQs) {
  bmstu::list<int> my_list_1({0, 1, 2, 3, 4, 5, 6});
  bmstu::list<int> my_list_2({0, 1, 2, 3, 4, 5, 6});
  bmstu::list<int> my_list_3({0, 1, 2, 3, 4, 5, 7});
  bmstu::list<int> my_list_4({1, 2, 3, 4, 5, 7, 8});
  bmstu::list<int> my_list_5({1, 1, 2, 3, 4, 5, 7});

  ASSERT_TRUE(my_list_1 == my_list_2);
  ASSERT_FALSE(my_list_1 == my_list_3);
  ASSERT_TRUE(my_list_1 != my_list_3);
  ASSERT_FALSE(my_list_1 != my_list_2);
  ASSERT_TRUE(my_list_1 < my_list_4);
  ASSERT_TRUE(my_list_4 > my_list_1);
  ASSERT_TRUE(my_list_1 <= my_list_5);
  ASSERT_TRUE(my_list_5 >= my_list_1);
}

TEST(ListTest, LeftShift) {
  bmstu::list<int> my_list({0, 1, 2, 3, 4, 5, 6});
  std::stringstream ss;
  ss << my_list;
  ASSERT_STREQ(ss.str().c_str(), "[ 0, 1, 2, 3, 4, 5, 6 ]");
}

TEST(ListTest, IteratorsHard) {
  bmstu::list<int> my_list_1({0, 1, 2, 3, 4});
  bmstu::list<int>::iterator it_b_1 = my_list_1.begin() + 1;
  bmstu::list<int>::iterator it_e_1 = my_list_1.end() - 1;

  bmstu::list<int> my_list_2(it_b_1, it_e_1);
  bmstu::list<int>::iterator it_b_2 = my_list_2.begin();
  bmstu::list<int>::iterator it_e_2 = my_list_2.end();

  ASSERT_EQ(my_list_1.size(), 5);
  ASSERT_EQ(my_list_2.size(), 3);
  for (int a = 1; it_b_2 != it_e_2; ++it_b_2, ++a) {
    ASSERT_TRUE(*it_b_2 == a);
    ASSERT_TRUE(my_list_2[a - 1] == a);
  }

  --it_e_2;
  it_b_2 = my_list_2.begin() - 1;
  for (int a = 3; it_b_2 != it_e_2; --it_e_2, --a) {
    ASSERT_TRUE(*it_e_2 == a);
    ASSERT_TRUE(my_list_2[a - 1] == a);
  }
}

class BmstuListlistTests : public ::testing::Test {
 protected:
  void SetUp() {
  }

  void TearDown() {
  }
};

TEST_F(BmstuListlistTests, init) {
  using namespace std;  // NOLINT
  {
    const bmstu::list<int> empty_int_list;
    ASSERT_EQ(empty_int_list.size(), 0u);
    ASSERT_TRUE(empty_int_list.empty());
  }

  {
    const bmstu::list<string> empty_string_list;
    ASSERT_EQ(empty_string_list.size(), 0u);
    ASSERT_TRUE(empty_string_list.empty());
  }
}

TEST_F(BmstuListlistTests, push_front) {
  using namespace std;  // NOLINT
  // Шпион, следящий за своим удалением

  // Проверка вставки в начало
  {
    bmstu::list<int> l;
    ASSERT_TRUE(l.empty());
    ASSERT_EQ(l.size(), 0u);

    l.push_front(0);
    l.push_front(1);
    ASSERT_EQ(l.size(), 2);
    ASSERT_TRUE(!l.empty());

    l.clear();
    ASSERT_EQ(l.size(), 0);
    ASSERT_TRUE(l.empty());
  }
}

TEST_F(BmstuListlistTests, PushBack) {
  using namespace std;  // NOLINT

  // Шпион, следящий за своим удалением

  // Проверка вставки в начало
  {
    bmstu::list<int> l;
    ASSERT_TRUE(l.empty());
    ASSERT_EQ(l.size(), 0u);

    l.push_back(1);
    l.push_back(1);
    l.push_back(3);
    ASSERT_EQ(l.size(), 3);
    ASSERT_TRUE(!l.empty());

    l.clear();
    ASSERT_EQ(l.size(), 0);
    ASSERT_TRUE(l.empty());
  }
}

TEST_F(BmstuListlistTests, DeletionSpy) {
  struct DeletionSpy {
    DeletionSpy() = default;

    explicit DeletionSpy(int &instance_counter) noexcept  // NOLINT
        : instance_counter_ptr_(
        &instance_counter) {
      OnAddInstance();
    }

    DeletionSpy(const DeletionSpy &other) noexcept
        : instance_counter_ptr_(other.instance_counter_ptr_) {
      OnAddInstance();
    }

    DeletionSpy &operator=(const DeletionSpy &rhs) noexcept {
      if (this != &rhs) {
        auto rhs_copy(rhs);
        std::swap(instance_counter_ptr_, rhs_copy.instance_counter_ptr_);
      }
      return *this;
    }

    ~DeletionSpy() {
      OnDeleteInstance();
    }

   private:
    void OnAddInstance() noexcept {
      if (instance_counter_ptr_) {
        ++(*instance_counter_ptr_);
      }
    }

    void OnDeleteInstance() noexcept {
      if (instance_counter_ptr_) {
        ASSERT_NE(*instance_counter_ptr_, 0);
        --(*instance_counter_ptr_);
      }
    }

    int *instance_counter_ptr_ = nullptr;
  };
  // Проверка фактического удаления элементов
  {
    int item0_counter = 0;
    int item1_counter = 0;
    int item2_counter = 0;
    {
      bmstu::list<DeletionSpy> list;
      list.push_front(DeletionSpy{item0_counter});
      list.push_front(DeletionSpy{item1_counter});
      list.push_front(DeletionSpy{item2_counter});

      ASSERT_EQ(item0_counter, 1);
      ASSERT_EQ(item1_counter, 1);
      ASSERT_EQ(item2_counter, 1);
      list.clear();
      ASSERT_EQ(item0_counter, 0);
      ASSERT_EQ(item1_counter, 0);
      ASSERT_EQ(item2_counter, 0);

      list.push_front(DeletionSpy{item0_counter});
      list.push_front(DeletionSpy{item1_counter});
      list.push_front(DeletionSpy{item2_counter});
      ASSERT_EQ(item0_counter, 1);
      ASSERT_EQ(item1_counter, 1);
      ASSERT_EQ(item2_counter, 1);
    }
    ASSERT_EQ(item0_counter, 0);
    ASSERT_EQ(item1_counter, 0);
    ASSERT_EQ(item2_counter, 0);
  }
}

TEST_F(BmstuListlistTests, Throw) {
  // Вспомогательный класс, бросающий исключение после создания N-копии
  struct ThrowOnCopy {
    ThrowOnCopy() = default;

    explicit ThrowOnCopy(int &copy_counter) noexcept  // NOLINT
        : countdown_ptr(&copy_counter) {
    }

    ThrowOnCopy(const ThrowOnCopy &other)
        : countdown_ptr(other.countdown_ptr) {
      if (countdown_ptr) {
        if (*countdown_ptr == 0) {
          throw std::bad_alloc();
        } else {
          --(*countdown_ptr);
        }
      }
    }

    // Присваивание элементов этого типа не требуется
    ThrowOnCopy &operator=(const ThrowOnCopy &rhs) = delete;

    // Адрес счётчика обратного отсчёта. Если не равен nullptr, то уменьшается при каждом копировании.
    // Как только обнулится, конструктор копирования выбросит исключение
    int *countdown_ptr = nullptr;
  };
  // Проверка фактического удаления элементов
  {
    bool exception_was_thrown = false;
    // Последовательно уменьшаем счётчик копирований до нуля, пока не будет выброшено исключение
    for (int max_copy_counter = 5; max_copy_counter >= 0; --max_copy_counter) {
      // Создаём непустой список
      bmstu::list<ThrowOnCopy> list;
      list.push_front(ThrowOnCopy{});
      try {
        int copy_counter = max_copy_counter;
        list.push_front(ThrowOnCopy(copy_counter));
        // Если метод не выбросил исключение, список должен перейти в новое состояние
        ASSERT_EQ(list.size(), 2);
      } catch (const std::bad_alloc &) {
        exception_was_thrown = true;
        // После выбрасывания исключения состояние списка должно остаться прежним
        ASSERT_EQ(list.size(), 1);
        break;
      }
    }
    ASSERT_TRUE(exception_was_thrown);
  }
}

TEST_F(BmstuListlistTests, IteratorsEmpty) {
  // Итерирование по пустому списку
  {
    bmstu::list<int> list;
    // Константная ссылка для доступа к константным версиям begin()/end()
    const auto &const_list = list;

    // Итераторы begine и end у пустого диапазона равны друг другу
    ASSERT_EQ(list.begin(), list.end());
    ASSERT_EQ(const_list.begin(), const_list.end());
    ASSERT_EQ(list.cbegin(), list.cend());
    ASSERT_EQ(list.cbegin(), const_list.begin());
    ASSERT_EQ(list.cend(), const_list.end());
  }
}

TEST_F(BmstuListlistTests, IteratorsNonEmpty) {
  // Итерирование по непустому списку
  {
    bmstu::list<int> list;
    const auto &const_list = list;

    list.push_front(1);
    ASSERT_EQ(list.size(), 1u);
    ASSERT_TRUE(!list.empty());

    ASSERT_TRUE(const_list.begin() != const_list.end());
    ASSERT_TRUE(const_list.cbegin() != const_list.cend());
    ASSERT_TRUE(list.begin() != list.end());

    ASSERT_TRUE(const_list.begin() == const_list.cbegin());

    ASSERT_TRUE(*list.cbegin() == 1);  // NOLINT
    *list.begin() = -1;
    ASSERT_TRUE(*list.cbegin() == -1);  // NOLINT

    const auto old_begin = list.cbegin();
    list.push_front(2);
    ASSERT_EQ(list.size(), 2);

    const auto new_begin = list.cbegin();
    ASSERT_NE(new_begin, old_begin);
    // Проверка прединкремента
    {
      auto new_begin_copy(new_begin);
      ASSERT_EQ((++(new_begin_copy)), old_begin);
    }
    // Проверка постинкремента
    {
      auto new_begin_copy(new_begin);
      ASSERT_EQ(((new_begin_copy)++), new_begin);
      ASSERT_EQ(new_begin_copy, old_begin);
    }
    // Итератор, указывающий на позицию после последнего элемента равен итератору end()
    {
      auto old_begin_copy(old_begin);
      ASSERT_EQ((++old_begin_copy), list.end());
    }
  }
}

TEST_F(BmstuListlistTests, IteratorsDecrement) {
  // Итерирование по непустому списку
  {
    bmstu::list<int> list;
    const auto &const_list = list;

    list.push_back(100500);
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    ASSERT_EQ(list.size(), 4u);
    ASSERT_TRUE(!list.empty());

    ASSERT_TRUE(const_list.begin() != const_list.end());
    ASSERT_TRUE(const_list.cbegin() != const_list.cend());
    ASSERT_TRUE(list.begin() != list.end());

    ASSERT_TRUE(const_list.begin() == const_list.cbegin());

    ASSERT_EQ(*list.cbegin(), 100500);
    *list.begin() = -1;
    ASSERT_TRUE(*list.cbegin() == -1);  // NOLINT
    auto end_list = list.end();
    auto back = --end_list;
    ASSERT_EQ(*(end_list), 3);
  }
}

TEST_F(BmstuListlistTests, IteratorsDecrement2) {
  // Итерирование по непустому списку
  {
    bmstu::list<int> list;
    const auto &const_list = list;

    list.push_back(100500);
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_front(100501);
    ASSERT_EQ(*(--(--list.end())), 2);
    ASSERT_EQ(*(list.begin()), 100501);
  }
}

TEST_F(BmstuListlistTests, back) {
  {
    using namespace std;  // NOLINT
    bmstu::list<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    std::stringstream out;
    out << list;
    ASSERT_EQ(out.str(), "[ 1, 2, 3, 4 ]"s);
  }
  {
    using namespace std;  // NOLINT
    bmstu::list<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_front(-2);
    list.push_front(-1);
    std::stringstream out;
    out << list;
    ASSERT_EQ(out.str(), "[ -1, -2, 1, 2 ]"s);
  }
}

TEST_F(BmstuListlistTests, arithmetic) {
  {
    using namespace std;  // NOLINT
    bmstu::list<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    bmstu::list<int>::iterator it = list.begin();
    ASSERT_EQ(*((it + 1) + 1), 3);
    ASSERT_EQ(*((it + 3) - 1), 3);
  }
  {
    bmstu::list<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    bmstu::list<int>::iterator it = list.end();
    ASSERT_EQ(*(it - list.size()), 1);
  }
  {
    using namespace std;  // NOLINT
    bmstu::list<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    bmstu::list<int>::iterator it = list.begin();
    ASSERT_EQ(*(it + 1), 2);
  }
}

TEST_F(BmstuListlistTests, distance) {
  bmstu::list<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);
  list.push_back(5);
  ASSERT_EQ(*list.begin(), 1);
  ASSERT_EQ(*(list.begin() + 1), 2);
  ASSERT_EQ(*(list.begin() + 2), 3);
  ASSERT_EQ((list.end() - list.begin()), 5);
  ASSERT_EQ(std::distance(list.begin(), list.end()), 5);
}

TEST_F(BmstuListlistTests, operators) {
  bmstu::list<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);
  list.push_back(5);
  ASSERT_EQ(list[0], 1);
  ASSERT_EQ(list[1], 2);
  ASSERT_EQ(list[2], 3);
  list[1] = 100500;
}

TEST_F(BmstuListlistTests, initializer_list) {
  bmstu::list<int> list{1, 2, 3, 4, 5, 6};
  ASSERT_EQ(list[0], 1);
  ASSERT_EQ(list[list.size() - 1], 6);
}

TEST_F(BmstuListlistTests, initializer_list_strings) {
  using namespace std;  // NOLINT
  bmstu::list<std::string>
      list{"first1"s, "first2"s, "first3"s, "first4"s, "first5"s, "first6"s};
  ASSERT_EQ(*list.begin(), "first1"s);
}

TEST_F(BmstuListlistTests, IteratorsOperator) {
  // Проверка оператора ->
  {
    using namespace std;  // NOLINT
    bmstu::list<std::string> string_list;

    string_list.push_front("one"s);
    ASSERT_EQ(string_list.cbegin()->length(), 3u);
    string_list.begin()->push_back('!');
    ASSERT_EQ(*string_list.begin(), std::string("one!"));
  }
}

TEST_F(BmstuListlistTests, Equals) {
  bmstu::list<int> list1{1, 2, 3, 4, 5, 6};
  bmstu::list<int> list1_1{1, 2, 3, 4, 5, 6};
  bmstu::list<int> list3{1, 2, 3, 3, 5, 6};
  bmstu::list<int> list2{666, 667, 668};
  ASSERT_FALSE(list1 == list2);
  ASSERT_FALSE(list1 == list3);
  ASSERT_TRUE(list1 == list1_1);
  // std::cout << list2 << list1 << std::endl;
}

TEST_F(BmstuListlistTests, IteratorsPolyForm) {
  // Проверка оператора ->
  // Преобразование итераторов
  {
    bmstu::list<int> list;
    list.push_front(1);
    // Конструирование ConstItrator из Iterator
    bmstu::list<int>::const_iterator const_it(list.begin());
    ASSERT_EQ(const_it, list.cbegin());
    ASSERT_EQ(*const_it, *list.cbegin());

    bmstu::list<int>::const_iterator const_it1;
    // Присваивание const_iterator-у значения Iterator
    const_it1 = list.begin();
    ASSERT_EQ(const_it1, const_it);
  }
}

TEST_F(BmstuListlistTests, Equals2) {
  // Проверка списков на равенство и неравенство
  bmstu::list<int> list_1;
  list_1.push_front(1);
  list_1.push_front(2);

  bmstu::list<int> list_2;
  list_2.push_front(1);
  list_2.push_front(2);
  list_2.push_front(3);

  bmstu::list<int> list_1_copy;
  list_1_copy.push_front(1);
  list_1_copy.push_front(2);

  bmstu::list<int> empty_list;
  bmstu::list<int> another_empty_list;

  // Список равен самому себе
  ASSERT_TRUE(list_1 == list_1);
  ASSERT_TRUE(empty_list == empty_list);

  // Списки с одинаковым содержимым равны, а с разным - не равны
  ASSERT_TRUE(list_1 == list_1_copy);
  ASSERT_TRUE(list_1 != list_2);
  ASSERT_TRUE(list_2 != list_1);
  ASSERT_TRUE(empty_list == another_empty_list);
}

TEST_F(BmstuListlistTests, Swap) {
  bmstu::list<int> list_1{1, 2, 3};
  bmstu::list<int> list_2{-1, -2};
  list_1.swap(list_2);
  ASSERT_EQ(list_1, (bmstu::list<int>{-1, -2}));
}

TEST_F(BmstuListlistTests, Swap2) {
  // Обмен содержимого списков

  bmstu::list<int> first;
  first.push_back(1);
  first.push_back(2);

  bmstu::list<int> second;
  second.push_back(10);
  second.push_back(11);
  second.push_back(15);

  const auto old_first_begin = first.begin();
  const auto old_second_begin = second.begin();
  const auto old_first_size = first.size();
  const auto old_second_size = second.size();

  first.swap(second);

  ASSERT_EQ(second.begin(), old_first_begin);
  ASSERT_EQ(first.begin(), old_second_begin);
  ASSERT_EQ(second.size(), old_first_size);
  ASSERT_EQ(first.size(), old_second_size);

  // Обмен при помощи функции swap
  {
    using std::swap;

    // В отсутствие пользовательской перегрузки будет вызвана функция std::swap, которая
    // выполнит обмен через создание временной копии
    swap(first, second);

    // Убеждаемся, что используется не std::swap, а пользовательская перегрузка

    // Если бы обмен был выполнен с созданием временной копии,
    // то итератор first.begin() не будет равен ранее сохранённому значению,
    // так как копия будет хранить свои узлы по иным адресам
    ASSERT_EQ(first.begin(), old_first_begin);
    ASSERT_EQ(second.begin(), old_second_begin);
    ASSERT_EQ(first.size(), old_first_size);
    ASSERT_EQ(second.size(), old_second_size);
  }
}

TEST_F(BmstuListlistTests, FromVector) {
  using namespace std;  // NOLINT
  std::vector<std::string> my_vec =
      {"string1"s, "string3"s, "string4"s, "string5"s, "string6"s, "string7"s};
  bmstu::list<std::string> my_list(my_vec.begin(), my_vec.end());
  my_list.push_front("begin_string"s);
  my_list.push_back("end_string"s);
  my_vec.clear();
  my_vec.insert(my_vec.begin(), my_list.begin(), my_list.end());

  ASSERT_EQ((std::vector<std::string>{"begin_string"s, "string1"s, "string3"s,
                                      "string4"s, "string5"s, "string6"s,
                                      "string7"s, "end_string"s}), my_vec);
}
