#ifndef __PROJ_1__HPP
#define __PROJ_1__HPP

#include <map>
#include <set>
/* 
 * Project 1:  you need to implement this function.
 I promise that any of my test cases will have an empty 
 	map as the fourth parameter when called.
 If the puzzle IS solvable, return true AND make the mapping indicate the solution.
 If the puzzle is NOT solvable, it is enough to return false.

 See the project 1 write-up for a better description. 
 */


bool puzzleSolver(std::string s1, std::string s2, std::string s3, std::map<char, unsigned> & mapping);
bool puzzleSolverHelper(	
					std::string s1,
					std::string s2,
					std::string s3,
					std::map<char, unsigned> & mapping,
					std::set<int> &digits,
					std::set<char> &letters);


bool verifySolution(std::string s1, std::string s2, std::string s3, const std::map<char, unsigned> & mapping);
void printMap(std::map<char, unsigned> & mapping, std::set<int> &digits, std::set<char> &letters);
#endif