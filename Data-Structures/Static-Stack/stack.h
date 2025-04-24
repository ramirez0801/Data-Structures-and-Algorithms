#include <iostream>
#include "exception.h"

template <class T, int ARRAYSIZE = 1024>
class Stack
{
    private:
        T data[ARRAYSIZE];
        int top;

        void copyAll(const Stack<T,ARRAYSIZE>&);

    public:
        Stack();
        Stack(const Stack<T,ARRAYSIZE>&);

        bool isEmpty();
        bool isFull();

        void push(const T&);

        T pop();
        T getTop();

        Stack<T, ARRAYSIZE>& operator = (const Stack<T,ARRAYSIZE>&);

};


using namespace std;

template <class T, int ARRAYSIZE>
void Stack<T,ARRAYSIZE>::copyAll(const Stack<T,ARRAYSIZE>& s)
{
    int i(0);
    while(i < s.top)
    {
        data[i] = s.data[i];
        i++;
    }

    top = s.top;
}

template <class T, int ARRAYSIZE>
Stack<T,ARRAYSIZE>::Stack() : top(-1) { }

template <class T, int ARRAYSIZE>
Stack<T,ARRAYSIZE>::Stack(const Stack<T,ARRAYSIZE>& s)
{
    copyAll(s);
}

template <class T, int ARRAYSIZE>
bool Stack<T,ARRAYSIZE>::isEmpty()
{
    return top == -1;
}

template <class T, int ARRAYSIZE>
bool Stack<T,ARRAYSIZE>::isFull()
{
    return top == ARRAYSIZE - 1;
}

template <class T, int ARRAYSIZE>
void Stack<T,ARRAYSIZE>::push(const T& e)
{
    if(isFull())
    {
        throw Exception("Pila llena, push");
    }

    top++;
    data[top] = e;
}

template <class T, int ARRAYSIZE>
T Stack<T,ARRAYSIZE>::pop()
{
    if(isEmpty())
    {
        throw Exception("Pila vacia, pop");
    }

    return data[top--];

}

template <class T, int ARRAYSIZE>
T Stack<T,ARRAYSIZE>::getTop()
{
    if(isEmpty())
    {
        throw Exception("Pila vacia, getTop");
    }

    return data[top];
}