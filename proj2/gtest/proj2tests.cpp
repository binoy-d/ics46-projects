#include "gtest/gtest.h"
#include "LLQueue.hpp"
#include "proj2.hpp"
#include <string>

namespace{


// NOTE:  these are not intended as exhaustive tests.
	// This should get you started testing.
	// You should make your own additional tests for both queue
	// and for the social network question.
	// VERY IMPORTANT:  if your LLQueue is not templated, or if 
	//		it is not linked-list based, your score for this project
	//		will be zero.  Be sure your LLQueue compiles and runs 
	// 		with non-numeric data types. 

TEST(QueueTest, QueueTest1)
{
	LLQueue<int> a;
	a.enqueue(5);
	EXPECT_TRUE( a.front() == 5 );
}

TEST(QueueTest, QueueTest2)
{
	LLQueue<int> a;
	a.enqueue(5);
	a.enqueue(3);
	EXPECT_TRUE( a.front() == 5 );
}


TEST(QueueTest, QueueTest3)
{
	LLQueue<int> a;
	a.enqueue(5);
	a.enqueue(3);
	a.dequeue();
	EXPECT_TRUE( a.front() == 3 );
}


TEST(QueueTest, QueueTestString)
{
	LLQueue<std::string> a;
	a.enqueue("daniel");
	a.enqueue("john");
	a.enqueue("binoy");
	EXPECT_EQ(a.size(), 3);
	EXPECT_EQ(a.front(), "daniel");
}

TEST(QueueTest, QueueAssignAndDiff)
{
    LLQueue<std::string> a;
    a.enqueue("hello");
    LLQueue<std::string> b;
    b = a;
    b.enqueue("darn");
    b.dequeue();
    EXPECT_TRUE(a.front() != b.front() and b.front() == "darn");
}


TEST(GraphTest, GraphTest1)
{
	std::vector< std::vector<unsigned> > g1 = {
		{1,2}, {0,3}, {0,3}, {1,2}
	};
		std::vector<unsigned> pathLengths(4);
	std::vector<unsigned> numShortestPaths(4);
	
	countPaths(g1, 0, pathLengths, numShortestPaths);

	std::vector<unsigned> expPathLengths = {0, 1, 1, 2};
	std::vector<unsigned> expNumSP = {1, 1, 1, 2};
	EXPECT_EQ(pathLengths, expPathLengths);
	EXPECT_EQ(expNumSP, numShortestPaths);

}


TEST(GraphTest, GraphTest2)
{
	std::vector< std::vector<unsigned> > g1 = {
		{1, 2, 4}, {0,3}, {0,3}, {1,2,5}, {0, 5}, {3, 4}
	};
	
	std::vector<unsigned> pathLengths(6);
	std::vector<unsigned> numShortestPaths(6);
	
	countPaths(g1, 0, pathLengths, numShortestPaths);

	std::vector<unsigned> expPathLengths = {0, 1, 1, 2, 1, 2};
	std::vector<unsigned> expNumSP = {1, 1, 1, 2, 1, 1};

	EXPECT_EQ(pathLengths, expPathLengths);
	EXPECT_EQ(expNumSP, numShortestPaths);
}

TEST(GraphTest, GraphTest3)
{
	std::vector< std::vector<unsigned> > g1 = {
		{1, 2, 4}, {0,3}, {0,3}, {1,2,5, 7}, {0, 5, 6}, {3, 4}, {4, 7}, {3, 6},
	};
	
	std::vector<unsigned> pathLengths(8);
	std::vector<unsigned> numShortestPaths(8);
	
	countPaths(g1, 0, pathLengths, numShortestPaths);

	std::vector<unsigned> expPathLengths = {0, 1, 1, 2, 1, 2, 2, 3};
	std::vector<unsigned> expNumSP = {1, 1, 1, 2, 1, 1, 1, 3};

	EXPECT_EQ(pathLengths, expPathLengths);
	EXPECT_EQ(expNumSP, numShortestPaths);
}

TEST(GraphTest, GraphTest4)
{
	std::vector< std::vector<unsigned> > g1 = {
		{2, 3, 5},
        {3},
        {0, 5, 6},
        {0, 1}, 
        {5},
        {0, 2, 4,  6},
        {2, 5}
	};
	
	std::vector<unsigned> pathLengths(7);
	std::vector<unsigned> numShortestPaths(7);
	
	countPaths(g1, 0, pathLengths, numShortestPaths);

	std::vector<unsigned> expPathLengths = {0, 2, 1, 1, 2, 1, 2};
	std::vector<unsigned> expNumSP = {1, 1, 1, 1, 1, 1, 2};

	EXPECT_EQ(pathLengths, expPathLengths);
	EXPECT_EQ(expNumSP, numShortestPaths);
}








}
	