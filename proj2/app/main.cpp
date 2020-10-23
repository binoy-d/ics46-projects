#include "LLQueue.hpp"
#include <iostream>
int main()
{
    LLQueue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);
    q.print();
    q.dequeue();
    q.print();
    q.dequeue();
    q.print();
    std::cout<<q.front()<<std::endl;
    return 0;
}

