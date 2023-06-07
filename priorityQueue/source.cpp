#include <iostream>
#include "priorityQueue.hpp"

int main()
{
    PriorityQueue<char> q(4);
    q.push('A', 0); //adds A with lowest priority: 0
    q.push('B', 3);
    q.push('C', 2);
    q.push('D', 2);
    q.push('E', 1);
    //Example for catching logic error
    try {
        q.push('F', 5);
    }
    catch (const std::logic_error& err){
        std::cout << "Wrong priority!";
        throw;
    }

    std::cout << q.peek(); // B
    q.pop();

    std::cout << q.peek(); // C
    q.pop();

    std::cout << q.peek(); // D
    q.pop();

    std::cout << q.peek(); // E
    q.pop();

    std::cout << q.peek(); // A
    q.pop();


}
