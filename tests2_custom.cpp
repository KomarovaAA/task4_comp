
#include "gtest/gtest.h"
#include "Vector.hpp"
#include "Erase_params.hpp"

class vector_test2: public ::testing::TestWithParam<Erase_params<int>> {

};

TEST_P(vector_test2, erase2) {
    Erase_params<int> params = GetParam();
    Vector<int> vector(params.elements);
    vector.erase(vector.begin() + params.first, vector.begin() + params.last);
    EXPECT_EQ(vector.size(), params.result.size());
    Vector<int> result(params.result);
    EXPECT_EQ(vector, result);
}

std::initializer_list<int> elemets1_ = {1, 2, 3, 4, 5, 6, 7, 8, 9};
std::initializer_list<int> elemets2_ = {1, 2, 3, 4, 5, 6, 7, 8, 9};
std::initializer_list<int> result1_ = {1, 2, 6, 7, 8, 9};
std::initializer_list<int> result2_ = {4, 5, 6, 7, 8, 9};


INSTANTIATE_TEST_CASE_P(
        erase_params,
        vector_test2,
        ::testing::Values(
                Erase_params<int> {
                        elemets1_,
                        2,
                        5,
                        result1_
                },
                Erase_params<int> {
                        elemets2_,
                        0,
                        3,
                        result2_
                }
        )
);