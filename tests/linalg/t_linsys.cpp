/**
 * Unit tests for the Linear Algebra module's Linear Systems class
 */
#include "../../include/linalg/linsys.hpp"
#include <cstdint>
#include <cstdlib>
#include <gtest/gtest.h>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

const double TOLERANCE = 1e-3;

TEST(LinSysTest, SolveGauss) {
    std::vector<std::vector<double>> squareMat = {{3.0, 2.0, -4.0, 3.0},
                                                  {2.0, 3.0, 3.0, 15.0},
                                                  {5.0, -3, 1.0, 14.0}};
    gpmp::linalg::LinSys linSysSquare(squareMat);

    // execute solve_gauss method
    std::vector<double> solution = linSysSquare.solve_gauss();

    // expected solution for the test matrix
    std::vector<double> expected_sol = {3, 1, 2};

    // assert solution vector
    ASSERT_EQ(solution.size(), expected_sol.size());

    for (int i = 0; i < solution.size(); i++) {
        ASSERT_NEAR(solution[i], expected_sol[i], TOLERANCE);
    }
}

TEST(LinSysTest, DeterminantTest) {
    /*std::vector<std::vector<double>> squareMat = {
        {3.0, 2.0, -4.0, 3.0},
        {2.0, 3.0, 3.0, 15.0},
        {5.0, -3.0, 1.0, 14.0},
        {1.0, 1.0, 1.0, 6.0}};
    */

    std::vector<std::vector<double>> squareMat = {{2, 1}, {5, 3}};
    gpmp::linalg::LinSys linSysSquare(squareMat);

    double det = linSysSquare.determinant();

    double expectedDet = 1;

    ASSERT_DOUBLE_EQ(expectedDet, det);
}

TEST(LinSysTest, DeterminantTestB) {
    std::vector<std::vector<double>> squareMat = {{4, 4, 3, 1},
                                                  {2, 8, 8, 6},
                                                  {4, 3, 2, 2},
                                                  {4, 1, 5, 6}};

    gpmp::linalg::LinSys linSysSquare(squareMat);

    double det = linSysSquare.determinant();

    double expectedDet = -226;

    ASSERT_DOUBLE_EQ(expectedDet, det);
}

TEST(LinSysTest, LUDecompositionTest) {
    // Define a square matrix
    std::vector<std::vector<double>> squareMat = {{3.0, 2.0, -4.0, 3.0},
                                                  {2.0, 3.0, 3.0, 15.0},
                                                  {5.0, -3.0, 1.0, 14.0},
                                                  {1.0, 1.0, 1.0, 6.0}};

    // expected lower
    std::vector<std::vector<double>> L = {{1, 0, 0, 0},
                                          {0.666667, 1, 0, 0},
                                          {1.66667, -3.8, 1, 0},
                                          {0.333333, 0.2, 0.0410959, 1}};

    // expected upper
    std::vector<std::vector<double>> U = {{3, 2, -4, 3},
                                          {0, 1.66667, 5.66667, 13},
                                          {0, 0, 29.2, 58.4},
                                          {0, 0, 0, 0}};

    // Create a LinSys object
    gpmp::linalg::LinSys linSysSquare(squareMat);

    // execute LU decomposition
    auto LU_mtx = linSysSquare.lu_decomp();

    // Check the dimensions of L and U
    ASSERT_EQ(LU_mtx.first.size(), L.size());
    ASSERT_EQ(LU_mtx.second.size(), U.size());

    // Check each element of L and U against the expected values
    for (uint32_t i = 0; i < LU_mtx.first.size(); i++) {
        for (uint32_t j = 0; j < LU_mtx.first[i].size(); j++) {
            ASSERT_NEAR(LU_mtx.first[i][j], L[i][j], TOLERANCE);
            ASSERT_NEAR(LU_mtx.second[i][j], U[i][j], TOLERANCE);
        }
    }
}
