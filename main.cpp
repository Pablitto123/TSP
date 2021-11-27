#include "TSP.hpp"

#include <iostream>



//void print_matr(const CostMatrix& cmatr){
//    auto i_matr = cmatr.get_matrix();
//    for(auto row_it = i_matr.cbegin(); row_it < i_matr.cend(); row_it++){
//        for(auto col_it = row_it->cbegin(); col_it < row_it->cend(); col_it ++){
//            if( *col_it != INF)
//                std::cout << *col_it << ", ";
//            else
//                std::cout << "INF" << " ";
//        }
//        std::cout << std::endl;
//    }
//    std::cout << std::endl;
//}

int main() {
//   cost_matrix_t cm = {{INF, 10, 8,   19, 12},
//                      {10, INF, 20,  6,  3},
//                      {8,   20, INF, 4,  2},
//                      {19,  6,  4, INF,  7},
//                      {12,  3,  2,   7, INF}};
//    cost_matrix_t cm {
//            {INF, 12,   3,  45,   3},
//            {78, INF,  90,  21,   3},
//            { 5,  56, INF,  23,  98},
//            {12,   6,   8, INF,  34},
//            { 3,  98,   3,   2, INF}
//    };

//    auto min_vals = cost_matr.get_min_values_in_rows();
//    for(auto row = min_vals.cbegin(); row < min_vals.cend(); row++) {
//        std::cout << *row <<std::endl;
//    }
//    std::cout <<std::endl;
//    auto min_vals2 = cost_matr.get_min_values_in_cols();
//    for(auto row = min_vals2.cbegin(); row < min_vals2.cend(); row++) {
//        std::cout << *row <<std::endl;
//    }
    /* Rozwiązania:
     * 32 : 2 3 4 1 0
     * 32 : 1 4 3 2 0
     */

    cost_matrix_t cm {
            {INF, 12,   3,  45,   6},
            {78, INF,  90,  21,   3},
            { 5,  56, INF,  23,  98},
            {12,   6,   8, INF,  34},
            { 3,  98,   3,   2, INF}
    };
    CostMatrix cost_matr(cm);
    auto ss = StageState(cost_matr);
    auto path = ss.get_path();
    for( auto it = path.cbegin(); it < path.cend(); it++){
        std::cout << *it <<std::endl;
    }
    std::cout<<std::endl<<std::endl << ss.get_lower_bound() <<std::endl;

    /* Rozwiązanie:
     * 30 : 4 3 2 0 1
    */

//    cost_matrix_t cm {
//            {INF,  3,  4,  2,  7},
//            {3,  INF,  4,  6,  3},
//            {4,  4,  INF,  5,  8},
//            {2,  6,  5,  INF,  6},
//            {7,  3,  8,  6,  INF},
//    };

    /* Rozwiązania:
     * 19 : 4 3 0 2 1
     * 19 : 1 2 0 3 4
    */
    /*
    tsp_solutions_t solutions = solve_tsp(cm);


    for (auto elem : solutions) {
        std::cout << elem.lower_bound << " : ";
        for (auto pelem : elem.path) {
            std::cout << pelem << " ";
        }
        std::cout << "\n";
    }
    */
    return EXIT_SUCCESS;
}
