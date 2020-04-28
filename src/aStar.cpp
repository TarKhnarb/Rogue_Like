#include<bits/stdc++.h>
#include <iostream>
using namespace std;

#define ROW 21
#define COL 21

typedef pair<int, int> Pair;
typedef pair<double, pair<int, int>> pPair;
unsigned a,b;

/**
 * @brief called to know what axis value(x or y) must take entity, NEVER NEVER call this function before aStarSearch
 * @param xORy if true, return x axis value, false y axis value
 * @return if true, return x axis value, false y axis value
 */
unsigned path(bool xORy){
    if(xORy){
        return a;
    }else{
        return b;
    }
}

/**
 * @brief a cell of the array containing the parameters(f,g,h) needed to do aStar
 */
struct cell{
    int parent_i, parent_j;
    double f, g, h;    // f = g + h
};

/**
 * @brief check if cell is an obstacle
 * @param row row value to check
 * @param col column value to check
 * @return true if valid, false if not
 */
bool isValid(int row, int col){
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

/**
 *@brief check if cell is blocked (obstacle) or not
 * @param[in] grid bool containing obstacles and no-obstacles cells
 * @param row row nb of grid we are going to check
 * @param col column nb of grid we are going to check
 * @return true if cell grid[row][col] is not blocked, false if not
 */
bool isUnBlocked(int grid[][COL], int row, int col){
    if(grid[row][col] == 1)
        return (true);
    else
        return (false);
}

/**
 *
 * @param row row nb of grid we are going to check
 * @param col column nb of grid we are going to check
 * @param dest Pair cell containing x,y value of destination
 * @return true if destination reached, false ifnot
 */
bool isDestination(int row, int col, Pair dest){
    if (row == dest.first && col == dest.second)
        return (true);
    else
        return (false);
}

/**
 * @brief calculates distance bewteen 2 points using Manhattans distance (4 axis only)
 * @param row row nb of grid we are going to check
 * @param col column nb of grid we are going to check
 * @param dest Pair cell containing x,y value of destination
 * @return distance according to formula
 */
double calculateHValue(int row, int col, Pair dest){
    return ((double)(abs(row-dest.first) + abs(col-dest.second)));
}

/**
 * @brief recursive function to trace destination from start >> final function
 * @param cellDetails
 * @param dest Pair cell containing x,y value of destination
 */
void tracePath(cell cellDetails[][COL], Pair dest){
    int row = dest.first;
    int col = dest.second;

    stack<Pair> Path;

    while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col )){
        Path.push (make_pair (row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }
    Path.push (make_pair (row, col));

        for(unsigned i=0;i<2;++i){ //to have the next value (if i=3 have 2 step, i=4 have 3 step)
            pair<int,int> p = Path.top();
            Path.pop();
            if(i==1){
                a=p.first;
                b=p.second;
            }
        }
    return;
}

/**
 * @brief the aStar algorithm
 * @param grid bool grid containing the (0 & 1's)
 * @param src start Pair
 * @param dest destination Pair (goal)
 */
void aStarSearch(int grid[][COL], Pair src, Pair dest){
    if (!isValid(src.first, src.second)){//this is maybe useless in out case
        printf ("Source is invalid\n");
        return;
    }
    if (!isValid (dest.first, dest.second)){ //also this
        printf ("Destination is invalid\n");
        return;
    }

    //check if the start or destination is blocked (surrounded with obstacles >> impossible to reach)
    if (!isUnBlocked(grid, src.first, src.second) || !isUnBlocked(grid, dest.first, dest.second)){
        printf ("Source or the destination is blocked\n");
        return;
    }

    // If the destination cell is the same as source cell
    if (isDestination(src.first, src.second, dest)){
        printf ("We are already at the destination\n");
        return;
    }

    bool closedList[ROW][COL];
    memset(closedList, false, sizeof (closedList));
    cell cellDetails[ROW][COL];//parameters of cell

    unsigned  i,j;
    for (i=0; i<ROW; i++){
        for (j=0; j<COL; j++){
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    // Initialising the parameters of the starting node
    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    set<pPair> openList;
    openList.insert(make_pair (0.0, make_pair (i, j)));
    bool foundDest = false;

    while (!openList.empty()){
        pPair p = *openList.begin();

        openList.erase(openList.begin());
        // Add this vertex to the closed list
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        double gNew, hNew, fNew;

        //----------- 1st Successor (North) ------------
        if(isValid(i-1, j)){
            if (isDestination(i-1, j, dest)){
                // Set the Parent of the destination cell
                cellDetails[i-1][j].parent_i = i;
                cellDetails[i-1][j].parent_j = j;
                printf ("The destination cell is found\n");
                tracePath (cellDetails, dest);
                foundDest = true;
                return;
            }
            else if (!closedList[i-1][j] && isUnBlocked(grid, i-1, j))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue (i-1, j, dest);
                fNew = gNew + hNew;

                if (cellDetails[i-1][j].f == FLT_MAX ||
                    cellDetails[i-1][j].f > fNew)
                {
                    openList.insert( make_pair(fNew,
                                               make_pair(i-1, j)));

                    // Update the details of this cell
                    cellDetails[i-1][j].f = fNew;
                    cellDetails[i-1][j].g = gNew;
                    cellDetails[i-1][j].h = hNew;
                    cellDetails[i-1][j].parent_i = i;
                    cellDetails[i-1][j].parent_j = j;
                }
            }
        }

        //----------- 2nd Successor (South) ------------
        if (isValid(i+1, j)){
            if (isDestination(i+1, j, dest)){
                // Set the Parent of the destination cell
                cellDetails[i+1][j].parent_i = i;
                cellDetails[i+1][j].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
            else if (!closedList[i+1][j] && isUnBlocked(grid, i+1, j))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i+1, j, dest);
                fNew = gNew + hNew;

                if (cellDetails[i+1][j].f == FLT_MAX ||
                    cellDetails[i+1][j].f > fNew)
                {
                    openList.insert( make_pair (fNew, make_pair (i+1, j)));
                    // Update the details of this cell
                    cellDetails[i+1][j].f = fNew;
                    cellDetails[i+1][j].g = gNew;
                    cellDetails[i+1][j].h = hNew;
                    cellDetails[i+1][j].parent_i = i;
                    cellDetails[i+1][j].parent_j = j;
                }
            }
        }

        //----------- 3rd Successor (East) ------------
        if (isValid (i, j+1)){
            if (isDestination(i, j+1, dest)){
                // Set the Parent of the destination cell
                cellDetails[i][j+1].parent_i = i;
                cellDetails[i][j+1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

            else if (!closedList[i][j+1] && isUnBlocked (grid, i, j+1))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue (i, j+1, dest);
                fNew = gNew + hNew;

                if (cellDetails[i][j+1].f == FLT_MAX ||
                    cellDetails[i][j+1].f > fNew)
                {
                    openList.insert( make_pair(fNew,
                                               make_pair (i, j+1)));

                    // Update the details of this cell
                    cellDetails[i][j+1].f = fNew;
                    cellDetails[i][j+1].g = gNew;
                    cellDetails[i][j+1].h = hNew;
                    cellDetails[i][j+1].parent_i = i;
                    cellDetails[i][j+1].parent_j = j;
                }
            }
        }

        //----------- 4th Successor (West) ------------
        if (isValid(i, j-1)){
            if (isDestination(i, j-1, dest)){
                // Set the Parent of the destination cell
                cellDetails[i][j-1].parent_i = i;
                cellDetails[i][j-1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

            else if (!closedList[i][j-1] && isUnBlocked(grid, i, j-1))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j-1, dest);
                fNew = gNew + hNew;


                if (cellDetails[i][j-1].f == FLT_MAX ||
                    cellDetails[i][j-1].f > fNew)
                {
                    openList.insert( make_pair (fNew,
                                                make_pair (i, j-1)));

                    // Update the details of this cell
                    cellDetails[i][j-1].f = fNew;
                    cellDetails[i][j-1].g = gNew;
                    cellDetails[i][j-1].h = hNew;
                    cellDetails[i][j-1].parent_i = i;
                    cellDetails[i][j-1].parent_j = j;
                }
            }
        }
    }

    // When the destination cell is not found and the open
    // list is empty, then we conclude that we failed to
    // reach the destiantion cell. This may happen when the
    // there is no way to destination cell (due to blockages)
    if (!foundDest)
        printf("Failed to find the Destination Cell\n");

    return;
}






////////////////////////////////////////////////////
/// Example
////////////////////////////////////////////////////

    //the four(4) things to do to use aAtar algo
    //make grid // 1--> The cell is free
                // 0--> The cell is obstacle
    int grid[ROW][COL];
    Pair src = make_pair(8, 0);  //give coordinates of start       (must be inside grid)
    Pair dest = make_pair(0, 0); //give coordinates of destination (must be inside grid)
    aStarSearch(grid,src,dest);        //start algorithm
    //never call these without having done the four (4) things before
    //give these to to entity for them to move
    path(true);                        //return x axis value
    path(false);                       //return y axis value

