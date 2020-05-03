#include "aStar.h"

Result result;

unsigned pathX(){
    return result.a;
}

unsigned pathY(){
    return result.b;
}

bool isValid(int row, int col){
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

bool isUnBlocked(int grid[][COL], int row, int col){
    if(grid[row][col] == 0)
        return (true);
    else
        return (false);
}

bool isDestination(int row, int col, Pair dest){
    if (row == dest.first && col == dest.second)
        return (true);
    else
        return (false);
}

double calculateHValue(int row, int col, Pair dest){
    return ((double)(abs(row-dest.first) + abs(col-dest.second)));
}

void tracePath(cell cellDetails[][COL], Pair dest, unsigned parameter){
    int row = dest.first;
    int col = dest.second;

    std::stack<Pair> Path;

    while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col )){
        Path.push (std::make_pair (row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }
    Path.push (std::make_pair (row, col));

    // Compute result
    while (parameter >= 1 && Path.size() >= 2){
        parameter--;
        Path.pop();
    }

    std::pair<int,int> p = Path.top();
    result.a = p.first;
    result.b = p.second;

    return;
}

void aStarSearch(int grid[][COL], Pair src, Pair dest, unsigned parameter){
    if (!isValid(src.first, src.second)){//this is maybe useless in out case
        std::cerr << "Source is invalid" << std::endl;
        return;
    }
    if (!isValid (dest.first, dest.second)){ //also this
        std::cerr << "Destination is invalid" << std::endl;
        return;
    }

    //check if the start or destination is blocked (surrounded with obstacles >> impossible to reach)
    if (!isUnBlocked(grid, src.first, src.second) || !isUnBlocked(grid, dest.first, dest.second)){
        std::cerr << "Source or the destination is blocked" << std::endl;
        return;
    }

    // If the destination cell is the same as source cell
    if (isDestination(src.first, src.second, dest)){
        std::cerr << "We are already at the destination" << std::endl;
        return;
    }

    bool closedList[ROW][COL];
    std::memset(closedList, false, sizeof (closedList));
    cell cellDetails[ROW][COL];//parameters of cell

    unsigned  i,j;
    for(unsigned i = 0; i < ROW; i++){
        for (unsigned j = 0; j < COL; j++){
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

    std::set<pPair> openList;
    openList.insert(std::make_pair (0.0, std::make_pair (i, j)));
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
                // destination cell has been found
                tracePath (cellDetails, dest);
                foundDest = true;
                return;
            }
            else if (!closedList[i-1][j] && isUnBlocked(grid, i-1, j))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue (i-1, j, dest);
                fNew = gNew + hNew;

                if (cellDetails[i-1][j].f == FLT_MAX || cellDetails[i-1][j].f > fNew)
                {
                    openList.insert( std::make_pair(fNew, std::make_pair(i-1, j)));

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
                // destination cell has been found
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
                    openList.insert( std::make_pair (fNew, std::make_pair (i+1, j)));
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
                // destination cell has been found
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

            else if (!closedList[i][j+1] && isUnBlocked (grid, i, j+1))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue (i, j+1, dest);
                fNew = gNew + hNew;

                if (cellDetails[i][j+1].f == FLT_MAX || cellDetails[i][j+1].f > fNew)
                {
                    openList.insert( std::make_pair(fNew, std::make_pair (i, j+1)));

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
                // destination cell has been found
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

            else if (!closedList[i][j-1] && isUnBlocked(grid, i, j-1))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j-1, dest);
                fNew = gNew + hNew;


                if (cellDetails[i][j-1].f == FLT_MAX || cellDetails[i][j-1].f > fNew)
                {
                    openList.insert( std::make_pair (fNew, std::make_pair (i, j-1)));

                    // Update the details of this cell
                    cellDetails[i][j-1].f = fNew;
                    cellDetails[i][j-1].g = gNew;
                    cellDetails[i][j-1].h = hNew;
                    cellDetails[i][j-1].parent_i = i;
                    cellDetails[i][j-1].parent_j = j;
                }
            }
        }
        
        //----------- 5th Successor (North-East) ------------ 
  
        if (isValid(i-1, j+1) == true) 
        { 
            if (isDestination(i-1, j+1, dest) == true) 
            { 
                cellDetails[i-1][j+1].parent_i = i; 
                cellDetails[i-1][j+1].parent_j = j; 
                tracePath (cellDetails, dest); 
                foundDest = true; 
                return; 
            } 
  
            else if (closedList[i-1][j+1] == false && isUnBlocked(grid, i-1, j+1) == true) 
            { 
                gNew = cellDetails[i][j].g + 1.414; 
                hNew = calculateHValue(i-1, j+1, dest); 
                fNew = gNew + hNew; 
  
                if (cellDetails[i-1][j+1].f == FLT_MAX || cellDetails[i-1][j+1].f > fNew) 
                { 
                    openList.insert( std::make_pair (fNew, std::make_pair(i-1, j+1))); 
  
                    cellDetails[i-1][j+1].f = fNew; 
                    cellDetails[i-1][j+1].g = gNew; 
                    cellDetails[i-1][j+1].h = hNew; 
                    cellDetails[i-1][j+1].parent_i = i; 
                    cellDetails[i-1][j+1].parent_j = j; 
                } 
            } 
        } 
  
        //----------- 6th Successor (North-West) ------------ 
  
        if (isValid (i-1, j-1) == true) 
        { 
            if (isDestination (i-1, j-1, dest) == true) 
            {  
                cellDetails[i-1][j-1].parent_i = i; 
                cellDetails[i-1][j-1].parent_j = j; 
                tracePath (cellDetails, dest); 
                foundDest = true; 
                return; 
            } 
  
            else if (closedList[i-1][j-1] == false && isUnBlocked(grid, i-1, j-1) == true) 
            { 
                gNew = cellDetails[i][j].g + 1.414; 
                hNew = calculateHValue(i-1, j-1, dest); 
                fNew = gNew + hNew; 
  
                if (cellDetails[i-1][j-1].f == FLT_MAX || cellDetails[i-1][j-1].f > fNew) 
                { 
                    openList.insert( std::make_pair (fNew, std::make_pair (i-1, j-1))); 
                    cellDetails[i-1][j-1].f = fNew; 
                    cellDetails[i-1][j-1].g = gNew; 
                    cellDetails[i-1][j-1].h = hNew; 
                    cellDetails[i-1][j-1].parent_i = i; 
                    cellDetails[i-1][j-1].parent_j = j; 
                } 
            } 
        } 
  
        //----------- 7th Successor (South-East) ------------ 
  
        if (isValid(i+1, j+1) == true) 
        { 
            if (isDestination(i+1, j+1, dest) == true) 
            { 
                cellDetails[i+1][j+1].parent_i = i; 
                cellDetails[i+1][j+1].parent_j = j; 
                tracePath (cellDetails, dest); 
                foundDest = true; 
                return; 
            } 
  
            else if (closedList[i+1][j+1] == false && isUnBlocked(grid, i+1, j+1) == true) 
            { 
                gNew = cellDetails[i][j].g + 1.414; 
                hNew = calculateHValue(i+1, j+1, dest); 
                fNew = gNew + hNew; 
  
                if (cellDetails[i+1][j+1].f == FLT_MAX || cellDetails[i+1][j+1].f > fNew) 
                { 
                    openList.insert(std::make_pair(fNew, std::make_pair (i+1, j+1))); 
  
                    cellDetails[i+1][j+1].f = fNew; 
                    cellDetails[i+1][j+1].g = gNew; 
                    cellDetails[i+1][j+1].h = hNew; 
                    cellDetails[i+1][j+1].parent_i = i; 
                    cellDetails[i+1][j+1].parent_j = j; 
                } 
            } 
        } 
  
        //----------- 8th Successor (South-West) ------------ 
  
        if (isValid (i+1, j-1) == true) 
        { 
            if (isDestination(i+1, j-1, dest) == true) 
            { 
                cellDetails[i+1][j-1].parent_i = i; 
                cellDetails[i+1][j-1].parent_j = j; 
                tracePath(cellDetails, dest); 
                foundDest = true; 
                return; 
            } 
  
            else if (closedList[i+1][j-1] == false && isUnBlocked(grid, i+1, j-1) == true) 
            { 
                gNew = cellDetails[i][j].g + 1.414; 
                hNew = calculateHValue(i+1, j-1, dest); 
                fNew = gNew + hNew;
                
                if (cellDetails[i+1][j-1].f == FLT_MAX || cellDetails[i+1][j-1].f > fNew) 
                { 
                    openList.insert(std::make_pair(fNew, std::make_pair(i+1, j-1))); 
  
                    cellDetails[i+1][j-1].f = fNew; 
                    cellDetails[i+1][j-1].g = gNew; 
                    cellDetails[i+1][j-1].h = hNew; 
                    cellDetails[i+1][j-1].parent_i = i; 
                    cellDetails[i+1][j-1].parent_j = j; 
                } 
            } 
        } 
    }

    // When the destination cell is not found and the open
    // list is empty, then we conclude that we failed to
    // reach the destiantion cell. This may happen when the
    // there is no way to destination cell (due to blockages)
    if (!foundDest){
        std::cerr << "Failed to find the destination cell" << std::endl;
        result.a = src.first;
        result.b = src.second;

        return;
    }

    tracePath(cellDetails, dest, parameter);
}
