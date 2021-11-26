//
// Created by Paweł on 26.11.2021.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "TSP.hpp"

TEST(CostMatr_test, min_in_rows){
    cost_matrix_t cm {
            {INF, 12,   3,  45,   6},
            {78, INF,  90,  21,   3},
            { 5,  56, INF,  23,  98},
            {12,   6,   8, INF,  34},
            { 3,  98,   3,   2, INF}
    };
    CostMatrix matr(cm);
    std::vector<cost_t> v = {3, 3, 5, 6, 2};
    EXPECT_EQ(matr.get_min_values_in_rows(),v);
}
TEST(CostMatr_test, min_in_cols){
    cost_matrix_t cm {
            {INF, 12,   3,  45,   6},
            {78, INF,  90,  21,   3},
            { 5,  56, INF,  23,  98},
            {12,   6,   8, INF,  34},
            { 3,  98,   3,   2, INF}
    };
    CostMatrix matr(cm);
    std::vector<cost_t> v = {3, 6, 3, 2, 3};
    EXPECT_EQ(matr.get_min_values_in_cols(),v);
}
