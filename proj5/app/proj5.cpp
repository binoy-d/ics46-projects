#include "proj5.hpp"
#include "MyPriorityQueue.hpp"
#include <iostream>

// As a reminder, for this project, edges have positive cost, g[i][j] = 0 means no edge.
std::vector<Edge> compute_mst(std::vector< std::vector<unsigned>> & graph)
{
	std::vector<Edge> mst;
	
	std::vector<bool> inTree(graph.size(), false);
	std::vector<unsigned> distances(graph.size(), std::numeric_limits<unsigned>::max());//distances start at inf
	MyPriorityQueue<Edge> toExplore;
	Edge first(0, 0, 0);
	toExplore.insert(first);
	distances[0] = 0;


	MyPriorityQueue<Edge> out;


	while(!done(inTree)){
		//pick node with shortest distance
		Edge popped = toExplore.min();
		toExplore.extractMin();
		unsigned i = popped.pt1;

		if(!inTree[i]){
			out.insert(popped);
			//mark as explored
			inTree[i] = true;

			//explore its nodes
			for(int j = 0; j<graph[i].size(); ++j){
				
				//if not in tree and less than prev
				if(graph[i][j]!=0 && !inTree[j] && graph[i][j]<distances[j]){
					Edge e(j,i,graph[i][j]);
					toExplore.insert(e);
					distances[j] = graph[i][j];
				}
			}
		}
		
		
	}

	out.extractMin();
	//dump queue to vector
	while(!out.isEmpty()){
		mst.push_back(out.min());
		out.extractMin();
	}
	return mst;
}

bool done(std::vector<bool> & inTree){
	for(int i = 0; i<inTree.size(); ++i){
		if(!inTree[i]){
			return false;
		}
	}
	return true;
}
// Returns the cost of the edges in the given vector,
// This does not confirm that it is a MST at all.  
unsigned mstCost(const std::vector<Edge> & vE) 
{
	unsigned sum =0;
	for(auto e: vE)
	{
		sum += e.weight;
	}
	return sum;
}

