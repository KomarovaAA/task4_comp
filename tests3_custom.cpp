//
// Created by Алена Комарова on 05.01.2021.
//

#include "gtest/gtest.h"
#include "Vector.hpp"
#include <fstream>
#include <type_traits>

template <class T>
struct input_output_test2: public ::testing::Test {
public:
    T createValue() {
        if constexpr(std::is_same<T, float>::value) {
            return 1;
        } else if constexpr(std::is_same<T, std::ofstream>::value) {
            return std::ofstream("out.txt");
        } else if constexpr(std::is_same<T, std::string>::value) {
            return "Hello, World!";
        }
    }
};
typedef ::testing::Types<float, std::string, std::ofstream> MyTypes;
TYPED_TEST_CASE(input_output_test2, MyTypes);

TYPED_TEST(input_output_test2, hy) {
    Vector<TypeParam> vector;
    vector.push_back(std::move(this->createValue()));
    EXPECT_EQ(vector.size(), 1);
}