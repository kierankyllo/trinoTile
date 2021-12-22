#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

//define global variable for tile number incrementation
int value = 0;

//define a struct for a point to facilitate returning a tuple from a function
struct point{
    int r,c;
};

//defines a function to print the 2d vector board to the display
void printBoard(vector<vector<int>> &board){
    for (int i = 0; i < board.size(); i++){
        for (int j = 0; j < board[i].size(); j++){
            printf( "%*d", 4, board[i][j] );
            }
    cout << endl;
    }
}

//defines a function to place a "hole" into the board as provided by the user
void makeHole(vector<vector<int>> &board, int r, int c){
    
    board[r][c] = -1;
}

//defines a function to locate the point value of the occupied hole square given the board and search parameters 
point findHole(vector<vector<int>> &board, int r, int c, int size){
    point defect = {-1,-1};
    for (int i = r; i < r + size; i++) {
        for (int j = c; j < c + size; j++) {
            if (board[i][j] != 0){
                defect.r = i;
                defect.c = j;
            }
        }
    }
    return defect;
}

//locates the quadrant of a point on the board given the board and search parameters
int findQuad(point &hole, int r, int c, int size){

    if (hole.r < r + size / 2 && hole.c < c + size / 2){
        return 1;
    }
    else if (hole.r < r + size / 2 && hole.c >= c + size / 2){
        return 2;
    }
    else if (hole.r >= r + size / 2 && hole.c < c + size / 2){
        return 3;
    }
    else if (hole.r >= r + size / 2 && hole.c >= c + size / 2){
        return 4;
    }
}

//defines a function to drop a tile in place on the board 2d vector object, increments the value of the tile to be placed, requires three sets of coordinates for blocks a, b, and c
void dropTile(vector<vector<int>> &board, int ar, int ac, int br, int bc, int cr, int cc){
    value++;
    if (board[ar][ac] == 0){board[ar][ac] = value;}
    if (board[br][bc] == 0){board[br][bc] = value;}
    if (board[cr][cc] == 0){board[cr][cc] = value;}
}

//defines a recursive devide and conquer algorithm to solve the board tiling problem.
//this function requires a board object with a single 1x1 tile occupied aith an integer value of -1.
//operating in three phases of recursion two of which have four cases as described below.
int solveBoard(vector<vector<int>> &board, int size, int r, int c){

    //base case, this is the end state of the recursive calls to each quadrant and subproblem 
    //when the problem is no longer reducable into sub problems this base case completes the tiling. 
   	if (size == 2) {
		value++;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (board[r + i][c + j] == 0) {
					board[r + i][c + j] = value;
				}
			}
		
        }
		return 0;
	}

    //these helper functions locate the occupied hole in the current context as well as the quadrant of the occupied hole
    //this allows for proper case handling for the algorithm to drop the properly oriented tile in place
    point hole = findHole(board, r, c, size);
    int quad = findQuad(hole, r, c, size);

    if (quad == 1){
        dropTile(board, r + size / 2, c + (size / 2) - 1, r + size / 2, c + size / 2, r + size / 2 - 1, c + size / 2);
    }
    // If missing Tile is in 3rd quadrant
    else if (quad == 3){
        dropTile(board, r + (size / 2) - 1, c + (size / 2), r + (size / 2), c + size / 2, r + (size / 2) - 1, c + (size / 2) - 1);
    }
    // If missing Tile is in 2nd quadrant
    else if (quad == 2){
        dropTile(board, r + size / 2, c + (size / 2) - 1, r + size / 2, c + size / 2, r + size / 2 - 1, c + size / 2 - 1);
    }
    // If missing Tile is in 4th quadrant
    else if (quad ==4){
        dropTile(board, r + (size / 2) - 1, c + (size / 2), r + (size / 2), c + (size / 2) - 1, r + (size / 2) - 1, c + (size / 2) - 1);    
    }

    //recursive phase of the algorithm divides the problem into sub problems and solves them recursively
	solveBoard(board, size / 2, r, c + size / 2);
	solveBoard(board, size / 2, r, c);
	solveBoard(board, size / 2, r + size / 2, c);
	solveBoard(board, size / 2, r + size / 2, c + size / 2);

	return 0;
}


//the main function facilitates the implementation of a basic user interface to collect initial conditions for the program and executes the solver
int main(){
    int n,x,y;
    cout << "Declare n >= 3: "; // Type a number and press enter
    cin >> n; // Get user input from the keyboard
    if (n < 3){
        printf("Value out of range");
        return 0;
    }
    int size = pow(2,n);

    cout << "Declare row index for hole: ";
    cin >> x;
    if (x > size){
        cout << "Value out of range"; 
        return 0;
        }
    cout << "Declare column index for hole: ";
    cin >> y;
    if (y > size){
        cout << "Value out of range"; 
        return 0;
        }

    vector<vector<int>> board(size,vector<int>(size));
    makeHole(board, x, y);
    solveBoard(board, size, 0, 0);
    printBoard(board);
    
    return 0;
}
