#include "TSP.hpp"

#include <algorithm>
#include <stack>
#include <optional>
#include <iostream>
std::ostream& operator<<(std::ostream& os, const CostMatrix& cm) {
    for (std::size_t r = 0; r < cm.size(); ++r) {
        for (std::size_t c = 0; c < cm.size(); ++c) {
            const auto& elem = cm[r][c];
            os << (is_inf(elem) ? "INF" : std::to_string(elem)) << " ";
        }
        os << "\n";
    }
    os << std::endl;

    return os;
}

/* PART 1 */

/**
 * Create path from unsorted path and last 2x2 cost matrix.
 * @return The vector of consecutive vertex.
 */
path_t StageState::get_path() {
    throw;  // TODO: Implement it!
}

/**
 * Get minimum values from each row and returns them.
 * @return Vector of minimum values in row.
 */
std::vector<cost_t> CostMatrix::get_min_values_in_rows() const {
    std::vector<cost_t> cost_vector(0);
    cost_t m_cost;
    for(auto row = matrix_.cbegin(); row<matrix_.cend(); ++row){
        m_cost = INF;
        for(auto col = row->cbegin(); col < row->cend(); ++col){
            m_cost = std::min(m_cost, *col);
        }
        cost_vector.push_back(m_cost);
    }
    return cost_vector;
}

/**
 * Reduce rows so that in each row at least one zero value is present.
 * @return Sum of values reduced in rows.
 */
cost_t CostMatrix::reduce_rows() {
    auto min_rows = get_min_values_in_rows();
    int sum = 0;
    auto min_it = min_rows.begin();
    for(auto row_it = matrix_.begin(); row_it < matrix_.end();++row_it){
        for(auto col_it = row_it->begin(); col_it < row_it->end(); ++col_it){
            if(*col_it != INF)
            *col_it -= *min_it;
        }
        sum += *min_it;
        min_it++;
    }
    return sum;
}

/**
 * Get minimum values from each column and returns them.
 * @return Vector of minimum values in columns.
 */
std::vector<cost_t> CostMatrix::get_min_values_in_cols() const {
    std::vector<cost_t> cost_vector(0);
    bool flag = false;
    for(auto row = matrix_.cbegin(); row<matrix_.cend(); ++row){
        auto cost_vector_it = cost_vector.begin();
        for(auto col = row->cbegin(); col < row->cend(); ++col){
            if(!flag) cost_vector.push_back(*col);
            else *cost_vector_it = std::min(*cost_vector_it, *col);
            if (cost_vector_it >= cost_vector.end())
                return std::vector<cost_t>(0);
            cost_vector_it++;

        }
        flag = true;
    }
    return cost_vector;
}

/**
 * Reduces rows so that in each column at least one zero value is present.
 * @return Sum of values reduced in columns.
 */
cost_t CostMatrix::reduce_cols() {
    auto min_cols = get_min_values_in_cols();
    int sum = 0;
    auto min_it = min_cols.cbegin();
    for(auto row_it = matrix_.begin(); row_it < matrix_.end();++row_it){
        min_it = min_cols.cbegin();
        for(auto col_it = row_it->begin(); col_it < row_it->end(); col_it++){
            if(*col_it != INF) {
                *col_it -= *min_it;
            }
            min_it++;
        }
    }

    for(auto it = min_cols.cbegin(); it < min_cols.cend(); it++){
        sum += *it;
    }
    return sum;
}

/**
 * Get the cost of not visiting the vertex_t (@see: get_new_vertex())
 * @param row
 * @param col
 * @return The sum of minimal values in row and col, excluding the intersection value.
 */
cost_t CostMatrix::get_vertex_cost(std::size_t row, std::size_t col) const {
    auto row_it = matrix_.cbegin() + row;
    int min_row = INF;
    for(auto it = row_it->cbegin(); it < row_it->cend();it++){
        if(it - row_it->cbegin() != col)
            min_row = std::min(*it,min_row);
    }
    int min_col = INF;
    for(auto it = matrix_.cbegin(); it < matrix_.cend(); it++){
        if(it - matrix_.cbegin() != row)
            min_col = std::min((*it)[col], min_col);
    }
    return min_col+min_row;
}

/* PART 2 */

/**
 * Choose next vertex to visit:
 * - Look for vertex_t (pair row and column) with value 0 in the current cost matrix.
 * - Get the vertex_t cost (calls get_vertex_cost()).
 * - Choose the vertex_t with maximum cost and returns it.
 * @return The coordinates of the next vertex.
 */
NewVertex StageState::choose_new_vertex() {
    int min_p = INF; //present minimum
    int min_l = INF; //last minimum
    std::size_t c_index;
    std::size_t r_index;
    vertex_t vert;
    for(auto row_it = matrix_.get_matrix().cbegin(); row_it < matrix_.get_matrix().cend(); row_it++){
        for(auto col_it = row_it->cbegin();col_it < row_it->cend(); col_it++){
            r_index = (std::size_t)(row_it - matrix_.get_matrix().cbegin());
            c_index = (std::size_t)(col_it - row_it->cbegin());
            if(*col_it == 0){
                min_p = std::min(min_p, matrix_.get_vertex_cost(r_index,c_index));
            }
            if(min_p < min_l){
                vert.col = c_index;
                vert.row = r_index;
            }
            min_l = min_p;
        }
    }
    auto n_V = NewVertex(vert);
    return n_V;
}

/**
 * Update the cost matrix with the new vertex.
 * @param new_vertex
 */
void StageState::update_cost_matrix(vertex_t new_vertex) {

    //make col INF

    for(auto it = matrix_.get_matrix().begin(); it < matrix_.get_matrix().end(); it++){
        (*it)[new_vertex.col] = INF;
    }
    auto row_it = matrix_.get_matrix().begin() + new_vertex.row;
    //make row INF
    for(auto it = row_it->begin(); it < row_it->end(); it++){
        (*it) = INF;
    }
}

/**
 * Reduce the cost matrix.
 * @return The sum of reduced values.
 */
cost_t StageState::reduce_cost_matrix() {
    return matrix_.reduce_rows() + matrix_.reduce_cols();
}

/**
 * Given the optimal path, return the optimal cost.
 * @param optimal_path
 * @param m
 * @return Cost of the path.
 */
cost_t get_optimal_cost(const path_t& optimal_path, const cost_matrix_t& m) {
    cost_t cost = 0;

    for (std::size_t idx = 1; idx < optimal_path.size(); ++idx) {
        cost += m[optimal_path[idx - 1] - 1][optimal_path[idx] - 1];
    }

    // Add the cost of returning from the last city to the initial one.
    cost += m[optimal_path[optimal_path.size() - 1] - 1][optimal_path[0] - 1];

    return cost;
}

/**
 * Create the right branch matrix with the chosen vertex forbidden and the new lower bound.
 * @param m
 * @param v
 * @param lb
 * @return New branch.
 */
StageState create_right_branch_matrix(cost_matrix_t m, vertex_t v, cost_t lb) {
    CostMatrix cm(m);
    cm[v.row][v.col] = INF;
    return StageState(cm, {}, lb);
}

/**
 * Retain only optimal ones (from all possible ones).
 * @param solutions
 * @return Vector of optimal solutions.
 */
tsp_solutions_t filter_solutions(tsp_solutions_t solutions) {
    cost_t optimal_cost = INF;
    for (const auto& s : solutions) {
        optimal_cost = (s.lower_bound < optimal_cost) ? s.lower_bound : optimal_cost;
    }

    tsp_solutions_t optimal_solutions;
    std::copy_if(solutions.begin(), solutions.end(),
                 std::back_inserter(optimal_solutions),
                 [&optimal_cost](const tsp_solution_t& s) { return s.lower_bound == optimal_cost; }
    );

    return optimal_solutions;
}

/**
 * Solve the TSP.
 * @param cm The cost matrix.
 * @return A list of optimal solutions.
 */
tsp_solutions_t solve_tsp(const cost_matrix_t& cm) {

    StageState left_branch(cm);

    // The branch & bound tree.
    std::stack<StageState> tree_lifo;

    // The number of levels determines the number of steps before obtaining
    // a 2x2 matrix.
    std::size_t n_levels = cm.size() - 2;

    tree_lifo.push(left_branch);   // Use the first cost matrix as the root.

    cost_t best_lb = INF;
    tsp_solutions_t solutions;

    while (!tree_lifo.empty()) {

        left_branch = tree_lifo.top();
        tree_lifo.pop();

        while (left_branch.get_level() != n_levels && left_branch.get_lower_bound() <= best_lb) {
            // Repeat until a 2x2 matrix is obtained or the lower bound is too high...

            if (left_branch.get_level() == 0) {
                left_branch.reset_lower_bound();
            }

            // 1. Reduce the matrix in rows and columns.
            cost_t new_cost = 0; // @TODO (KROK 1)

            // 2. Update the lower bound and check the break condition.
            left_branch.update_lower_bound(new_cost);
            if (left_branch.get_lower_bound() > best_lb) {
                break;
            }

            // 3. Get new vertex and the cost of not choosing it.
            NewVertex new_vertex = NewVertex(); // @TODO (KROK 2)

            // 4. @TODO Update the path - use append_to_path method.

            // 5. @TODO (KROK 3) Update the cost matrix of the left branch.

            // 6. Update the right branch and push it to the LIFO.
            cost_t new_lower_bound = left_branch.get_lower_bound() + new_vertex.cost;
            tree_lifo.push(create_right_branch_matrix(cm, new_vertex.coordinates,
                                                      new_lower_bound));
        }

        if (left_branch.get_lower_bound() <= best_lb) {
            // If the new solution is at least as good as the previous one,
            // save its lower bound and its path.
            best_lb = left_branch.get_lower_bound();
            path_t new_path = left_branch.get_path();
            solutions.push_back({get_optimal_cost(new_path, cm), new_path});
        }
    }

    return filter_solutions(solutions); // Filter solutions to find only optimal ones.
}
