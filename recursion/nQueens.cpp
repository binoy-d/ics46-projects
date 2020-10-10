/* Completed ;  you should start with a different file. 
  When presenting this in lecture
    - Emphasize what each piece means.
 */

#include <iostream>
#include <vector>

void printSolution(const std::vector<unsigned> & queens, unsigned n);
// This function assumes we have just placed or removed a 
// queen from position (row, column).  It will adjust 
// the threats in all rows after that by the given amount.
// Calling this with "change = +1" means we are placing a 
//      queen, while calling with "change = -1" means we 
//      have just removed a queen from the given spot. 
void changeThreats(unsigned row, unsigned column, int change, std::vector< std::vector<unsigned> > & threats, unsigned n);

// This function assumes we have placed one queen in each
// of rows [0 .. row-1] 
void search (unsigned row, std::vector<unsigned> & queens, std::vector< std::vector<unsigned> > & threats, unsigned n) 
{
    if (row==n) 
        printSolution(queens, n); //Show the layout
    // TODO:
}

// Now we also have to implement changeThreats.  
// Since we are only worrying about placing on 
// the rest of the board, we will only track 
// threats on rows after the current one.
// If change is "+1" we are adding a piece to the board
// and if it is "-1" we are removing one.
// This allows us to track *HOW MANY* threats to a square exist.

void changeThreats(unsigned row, unsigned column, int change, std::vector< std::vector<unsigned> > & threats, unsigned n)
{
// TODO
 
}

void printSeparator(int n)
{
    std::cout << "+";
    for(int j=0; j < n; j++)
    {
        std::cout << "-+";
    }
    std::cout << std::endl;

}

void printSolution(const std::vector<unsigned> & queens, unsigned n) 
{
    printSeparator(n);
    for(int i = 0; i < n; i++) 
    {
        std::cout << "|";
        for(int j = 0; j < n; j++) 
        {

            if (j == queens[i]) 
                std::cout << "Q|";
            else 
                std::cout << " |";
        }
        std::cout << std::endl;
        printSeparator(n);
      }
    std::cout << std::endl; 
}

int main(void) 
{
    /*
     * Each row will have exactly one queen, so we 
        have a vector q:  q[i] = j means that the 
        queen in row i is in column j.

     * Each square gets "threatened" by a queen if 
        she is on the same row, column, or diagonal 
        as the square.
        Because our strategy is going to be to place 
        queens on the 0th row, then the 1st row, etc
        and when we backtrack, we will remove the 
        highest-row queen that we have placed, we need 
        only track the threats in rows _ after_ the most 
        recent queen placement that is still on the board.
     */
    unsigned n; //size of the grid

    std::cin >> n;

    std::vector<unsigned> queens(n);
    std::vector< std::vector<unsigned> > threats(n, std::vector<unsigned> (n, 0)); 
  
    search(0, queens, threats, n);  // search *starting* at row 0.
    return 0;
}
