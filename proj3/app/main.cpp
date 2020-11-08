#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <set>

#include "proj3.hpp"
#include "Wordset.hpp"


int main()
{
    WordSet yes;
    std::string input = "abz";
    std::cout<<hashFunction(input, 41, 100000)<<std::endl;
    return 0;
}

