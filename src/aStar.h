#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <utility>
#include <stack>
#include <cstring>
#include <set>
#include <cfloat>

#define ROW 20
#define COL 40

typedef std::pair<int, int> Pair;
typedef std::pair<double, std::pair<int, int>> pPair;

struct Result{
    int a;
    int b;
};

/**
 * @brief a cell of the array containing the parameters(f,g,h) needed to do aStar
 */
struct cell{
    int parent_i, parent_j;
    double f, g, h;    // f = g + h
};

/** TODO change this oxygen
 * @brief called to know what axis value(x or y) must take entity, NEVER NEVER call this function before aStarSearch
 * @param xORy if true, return x axis value, false y axis value
 * @return if true, return x axis value, false y axis value
 */
unsigned pathX();
unsigned pathY();

/**
 * @brief check if cell is an obstacle
 * @param row row value to check
 * @param col column value to check
 * @return true if valid, false if not
 */
bool isValid(int row, int col);

/**
 *@brief check if cell is blocked (obstacle) or not
 * @param[in] grid bool containing obstacles and no-obstacles cells
 * @param row row nb of grid we are going to check
 * @param col column nb of grid we are going to check
 * @return true if cell grid[row][col] is not blocked, false if not
 */
bool isUnBlocked(int grid[][COL], int row, int col);

/**
 *
 * @param row row nb of grid we are going to check
 * @param col column nb of grid we are going to check
 * @param dest Pair cell containing x,y value of destination
 * @return true if destination reached, false ifnot
 */
bool isDestination(int row, int col, Pair dest);

/**
 * @brief calculates distance bewteen 2 points using Manhattans distance (4 axis only)
 * @param row row nb of grid we are going to check
 * @param col column nb of grid we are going to check
 * @param dest Pair cell containing x,y value of destination
 * @return distance according to formula
 */
double calculateHValue(int row, int col, Pair dest);

/**
 * @brief recursive function to trace destination from start >> final function
 * @param cellDetails
 * @param dest Pair cell containing x,y value of destination
 */
void tracePath(cell cellDetails[][COL], Pair dest);

/**
 * @brief the aStar algorithm
 * @param grid bool grid containing the (0 & 1's)
 * @param src start Pair
 * @param dest destination Pair (goal)
 */
void aStarSearch(int grid[][COL], Pair src, Pair dest);

#endif // ASTAR_H
