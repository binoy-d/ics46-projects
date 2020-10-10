// If you really want to make a program for the app, be my guest.
// You may prefer to do so in /exp instead.
// Or better yet, use gtest to automate your own test cases!
#include "proj1.hpp"
#include <iostream>
#include <map>
#include <string>
int main()
{
    std::string s1 = "UCI";
    std::string s2 = "ALEX";
    std::string s3 = "MIKE";

    std::map<char, unsigned> solution = {
        {'G', 1},
        {'O', 2},
        {'B', 3},
        {'A', 4},
        {'D', 5},
        {'N', 6},
        {'R', 7},
        {'L', 8},
        {'E', 9},
        {'T', 0},
    };

    std::map<char, unsigned> ayeyuh = {};

    std::cout<<puzzleSolver( s1, s2, s3, ayeyuh )<<std::endl;
    //std::cout<<verifySolution(s1, s2, s3, solution);

    return 0;
}




