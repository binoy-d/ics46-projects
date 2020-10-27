#include "LLQueue.hpp"
#include "proj2.hpp"
#include <vector>
#include <iostream>
int main()
{
    std::vector< std::vector<unsigned> > g1 = {
		{2, 3, 5},
        {3},
        {0, 5, 6},
        {0, 1}, 
        {5},
        {0, 2, 6},
        {2, 5}
	};
	std::vector<unsigned> pathLengths(7);
	std::vector<unsigned> numShortestPaths(7);
	
	
    countPaths(g1, 6, pathLengths, numShortestPaths);
    for(unsigned i = 0; i<7; ++i){
        std::cout<<pathLengths[i]<<",";
    }
    std::cout<<std::endl;
    
}

