#include <exception>
#include "MyQueue.hpp"

template<typename T>
class PriorityQueue
{
    size_t maxPriority;
    MyQueue<T>* queues;
    size_t elementsCount = 0;

    void free();
    void copyFrom(const PriorityQueue<T>& other);
      

public:
    PriorityQueue(size_t maxPriority);
    PriorityQueue(const PriorityQueue<T>& other);
    PriorityQueue<T>& operator=(const PriorityQueue<T>& other);
    ~PriorityQueue();

    void push(const T& obj, size_t priority);
    void push(T&& obj, size_t priority);
    void pop();

    const T& peek() const;
    bool isEmpty() const;

};

template<typename T>
bool PriorityQueue<T>::isEmpty() const
{
    return elementsCount == 0;
}

template<typename T>
void PriorityQueue<T>::free()
{
    delete[] queues;
}

template<typename T>
void PriorityQueue<T>::copyFrom(const PriorityQueue<T>& other)
{
    this->maxPriority = maxPriority;
    queues = new MyQueue<T>[maxPriority];
    for (size_t i = 0; i < maxPriority; i++)
        queues[i] = other.queues[i];
}

template<typename T>
PriorityQueue<T>::PriorityQueue(size_t maxPriority)
{
    if (maxPriority == 0)
        throw std::logic_error("You have to define priorities!");

    this->maxPriority = maxPriority;
    queues = new MyQueue<T>[maxPriority];
}

template<typename T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue<T>& other)
{
    copyFrom();
}

template<typename T>
PriorityQueue<T>& PriorityQueue<T>::operator=(const PriorityQueue<T>& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

template<typename T>
PriorityQueue<T>::~PriorityQueue()
{
    free();
}

template<typename T>
void PriorityQueue<T>::push(const T& obj, size_t priority)
{
    if (priority >= maxPriority)
        throw std::logic_error("No such priority!");
    elementsCount++;
    queues[priority].push(obj);
}

template<typename T>
void PriorityQueue<T>::push(T&& obj, size_t priority)
{
    if (priority >= maxPriority)
        throw std::logic_error("No such priority!");
    elementsCount++;
    queues[priority].push(std::move(obj));
}

template<typename T>
void PriorityQueue<T>::pop()
{

    if (isEmpty())
        throw std::logic_error("Empty queue!");

    for (int i = maxPriority - 1; i >= 0; i--)
    {
        if (!queues[i].isEmpty())
        {
            queues[i].pop();
            --elementsCount;
            return;
        }
    }
}

template<typename T>
const T& PriorityQueue<T>::peek() const
{

    for (int i = maxPriority - 1; i >= 0; i--)
    {
        if (!queues[i].isEmpty())
            return queues[i].peek();
    }
  
}


