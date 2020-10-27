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
        pathLengths[i] = 0;
    }

    //visit start node, and add to queue
    visited[start] = true;
    queue.enqueue(start);

    while(!queue.isEmpty()){
        //dequeue a vertex
        start = queue.front();
        queue.dequeue();
        std::cout<<start<<std::endl;

        for(unsigned i = 0; i<friends[start].size(); ++i){
            if(!visited[friends[start][i]]){
                visited[friends[start][i]] = true;
                pathLengths[friends[start][i]] = pathLengths[start]+1;
                queue.enqueue(friends[start][i]);
            }
        }
    }

}