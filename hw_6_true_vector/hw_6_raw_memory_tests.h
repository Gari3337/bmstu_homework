// Copyright 2024 <fleurs>

#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <utility>
#include <numeric>

#include "hw_6_raw_memory.h"
#pragma once

class WithoutDefaultConstructor {
  public:
    WithoutDefaultConstructor() = delete;

    explicit WithoutDefaultConstructor(int other) : number(other) {
    }

    int number;
};

TEST(truevector, test) {
  bmstu::raw_memory<WithoutDefaultConstructor> memory(10);
  memory(5);
}
