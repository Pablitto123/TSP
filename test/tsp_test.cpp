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


TEST(CostMatr_test, reduce_rows){
    cost_matrix_t cm {
            {INF, 12,   3,  45,   6},
            {78, INF,  90,  21,   3},
            { 5,  56, INF,  23,  98},
            {12,   6,   8, INF,  34},
            { 3,  98,   3,   2, INF}
    };
    cost_matrix_t cmt {
            {INF, 9, 0, 42, 3},
            {75, INF, 87, 18, 0},
            {0, 51, INF, 18, 93},
            {6, 0, 2, INF, 28},
            {1, 96, 1, 0, INF}
    };
    CostMatrix matr(cm);
    int sum = matr.reduce_rows();
    CostMatrix tmatr(cmt);
    EXPECT_EQ(matr.get_matrix(),tmatr.get_matrix());
    EXPECT_EQ(19, sum);
}


TEST(CostMatr_test, reduce_cols){
    cost_matrix_t cm {
            {INF, 12,   3,  45,   6},
            {78, INF,  90,  21,   3},
            { 5,  56, INF,  23,  98},
            {12,   6,   8, INF,  34},
            { 3,  98,   3,   2, INF}
    };
    cost_matrix_t cmt {
            {INF,6,    0,   43,  3},
            {75, INF,  87,  19,  0},
            {2,  50,   INF, 21,  95},
            {9,  0,    5,   INF, 31},
            {0,  92,   0,   0,   INF}
    };
    CostMatrix matr(cm);
    int sum = matr.reduce_cols();
    CostMatrix tmatr(cmt);
    EXPECT_EQ(matr.get_matrix(),tmatr.get_matrix());
    EXPECT_EQ(17, sum);
}

TEST(CostMatr_test, get_vertex_cost){
    cost_matrix_t cm {
            {INF, 12,   3,  45,   6},
            {78, INF,  90,  21,   3},
            { 5,  56, INF,  23,  98},
            {12,   6,   8, INF,  34},
            { 3,  98,   3,   2, INF}
    };
    cost_matrix_t cmt {
            {INF,6,    0,   43,  3},
            {75, INF,  87,  19,  0},
            {2,  50,   INF, 21,  95},
            {9,  0,    5,   INF, 31},
            {0,  92,   0,   0,   INF}
    };
    CostMatrix matr1(cm);
    CostMatrix matr2(cmt);
    int c1 = matr1.get_vertex_cost(1,2);
    int c2 = matr2.get_vertex_cost(1,2);
    int c3 = matr2.get_vertex_cost(0,2);
    int c4 = matr2.get_vertex_cost(3,1);
    int c5 = matr2.get_vertex_cost(3,1);
    int c6 = matr1.get_vertex_cost(0,0);
    int c7 = matr1.get_vertex_cost(4,4);
    EXPECT_EQ(6,c1);
    EXPECT_EQ(0, c2);
    EXPECT_EQ(3,c3);
    EXPECT_EQ(11, c4);
    EXPECT_EQ(11, c5);
    EXPECT_EQ(6, c6);
    EXPECT_EQ(5, c7);
}