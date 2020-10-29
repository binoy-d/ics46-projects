#include "proj2.hpp"
#include "LLQueue.hpp"
#include <vector>
#include <iostream>

void countPaths(const std::vector< std::vector<unsigned> > & friends, unsigned start, std::vector<unsigned> & pathLengths, std::vector<unsigned> & numShortestPaths)
{
    LLQueue<unsigned> queue;

    bool *visited = new bool[friends.size()];

    for(unsigned i = 0; i<friends.size(); ++i){
        visited[i] = false;
        pathLengths[i] = UINT_MAX;
        numShortestPaths[i] = 0;
    }

    numShortestPaths[start] = 1;
    pathLengths[start] = 0;
    visited[start] = true;
    
    queue.enqueue(start);

    while(!queue.isEmpty()){
        //dequeue a vertex
        unsigned current = queue.front();
        std::cout<<"Current: "<<current<<" | ";
        queue.dequeue();
        for(unsigned i = 0; i<friends[current].size(); ++i){
            unsigned f = friends[current][i];
            std::cout<<f<<" ";
            if(!visited[f]){
                visited[f] = true;
                queue.enqueue(f);
            }
            if(pathLengths[f]>pathLengths[current]+1){
                pathLengths[f] = pathLengths[current]+1;
                numShortestPaths[f] = numShortestPaths[current];
            }else if(pathLengths[f] == pathLengths[current]+1){
                numShortestPaths[f] += numShortestPaths[current];
            }
            
            
        }
        std::cout<<std::endl;
    }

}


