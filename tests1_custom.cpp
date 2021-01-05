//
// Created by Алена Комарова on 05.01.2021.
//
#include "gtest/gtest.h"
#include "Vector.hpp"

TEST(vector2, push_back2){
    Vector<int> vector;
    for (int i = 0; i < 10; i++) {
        vector.push_back(i * i);
    }
    EXPECT_EQ(10, vector.size());
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(i * i, vector.at(i));
    }
}

TEST(vector2, pop_back2) {
    Vector<int> vector;
    for (int i = 0; i < 10; i++) {
        vector.push_back(i * i);
    }
    for (int i = 9; i >= 0 ; i--) {
        EXPECT_EQ(i * i, vector.back());
        vector.pop_back();
    }
}

TEST(vector2, erase2) {
    Vector<int> vector;
    for (int i = 0; i < 10; i++) {
        vector.push_back(i * i);
    }
    vector.erase(vector.begin());
    EXPECT_EQ(1, vector.at(0));
    vector.erase(vector.begin(), std::prev(vector.end()));
    EXPECT_EQ(81, *vector.begin());
}

TEST(vector2, begin2) {
    Vector<int> vector;
    vector.push_back(10);
    vector.push_back(11);
    vector.push_back(12);
    EXPECT_EQ(10, *vector.begin());
    vector.erase(vector.begin());
    EXPECT_EQ(11, *vector.begin());
    vector.erase(vector.begin());
    EXPECT_EQ(12, *vector.begin());
}

TEST(vector2, end2) {
    Vector<int> vector;
    vector.push_back(10);
    vector.push_back(11);
    vector.push_back(12);
    EXPECT_EQ(12, *std::prev(vector.end()));
    vector.pop_back();
    EXPECT_EQ(11, *std::prev(vector.end()));
    vector.pop_back();
    EXPECT_EQ(10, *std::prev(vector.end()));
}

TEST(vector2, constructor_copy2) {
    Vector<int> vector1;
    for (int i = 0; i < 3; i++) {
        vector1.push_back(i + 1);
    }
    Vector<int> vector2(vector1);
    EXPECT_EQ(vector1, vector2);
}

TEST(vector2, constructor_remove2) {
    Vector<int> vector2(Vector<int>({10, 220, 10}));
    EXPECT_EQ(vector2.size(), 3);
}

TEST(vector2, operator_copy2) {
    Vector<int> vector({10, 220, 10});
    Vector<int> vector1 = vector;
    EXPECT_EQ(vector1, vector);
}

TEST(vector2, operator_remove2) {
    Vector<int> vector = Vector<int>({10, 20, 30});
    EXPECT_EQ(vector.size(), 3);
}

