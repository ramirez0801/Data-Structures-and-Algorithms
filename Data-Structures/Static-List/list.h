#include <iostream>
#include <fstream>

#include "exception.h"

template <class T, int arraysize = 1024>
class List
{
    private:
        T data[arraysize];
        int last;

        bool isValidPos(const int&);
        void copyAll(const List<T,arraysize> &);
    
    public:
        List();
        List(const List<T,arraysize>&);
    
        bool isEmpty();
        bool isFull();

        void insertData(const int&, const T&);

        void deleteData(const int&);

        int getFirst();
        int getLast();
        int getPrevPos(const int&);
        int getNextPos(const int&);

        T retrieve(const int&);

        std::string toString();

        void deleteAll();

        List<T, arraysize>& operator = (const List<T,arraysize>&);
};

using namespace std;

template <class T,int arraysize>
void List<T,arraysize>::copyAll(const List<T,arraysize>& l)
{
    int i(0);
    while(i <= l.last)
    {
        data[i] == l.data[i];
        i++
    }

    last = l.last;
}

template <class T,int arraysize>
bool List<T,arraysize>::isValidPos(const int& p)
{
    return p >= 0 and p <=last;
}

template <class T,int arraysize>
List<T,arraysize>::List() : last(-1) { }

template <class T,int arraysize>
List<T,arraysize>::List(const List<T,arraysize>& l)
{
    copyAll(l);
}

template <class T,int arraysize>
bool List<T,arraysize>::isEmpty()
{
    return last == -1;
}

template <class T,int arraysize>
bool List<T,arraysize>::isFull()
{
    return last == arraysize - 1;
}


template <class T,int arraysize>
void List<T,arraysize>::insertData(const int& p, const T& e)
{
    if(isFull())
    {
        throw ListException("Desbordamiento, insertData");
    }

    if(p == -1 and !isValidPos(p))
    {
        throw ListException("Poscicion Inavlida, insertData");
        return;
    }

    int i(last);
    while(i > p)
    {
        data[i + 1] = data[i];
        i--; 
    }

    data[p + 1] = e;
    last++;
}

template <class T,int arraysize>
void List<T,arraysize>::deleteData(const int& p)
{
    if(!isValidPos(p))
    {
        throw ListException("Posicion Invalida, deleteData");
        return;
    }

    int i(p);
    while(i < last)
    {
        data[i] = data[i+1];
        i++;
    }
    last--;
}

template <class T,int arraysize>
int List<T,arraysize>::getFirst()
{
    if(isEmpty())
    {
        return -1;
    }

    return 0;
}

template <class T,int arraysize>
int List<T,arraysize>::getLast()
{
    return last;
}

template <class T,int arraysize>
int List<T,arraysize>::getPrevPos(const int& p)
{
    if(p == getFirst() or !isValidPos(p))
    {
        return -1
    }

    return p - 1;
}

template <class T,int arraysize>
int List<T,arraysize>::getNextPos(const int& p)
{
    if(p == getLast() or !isValidPos(p))
    {
        return -1;
    }

    return p + 1; 
}

template <class T,int arraysize>
T List<T,arraysize>::retrieve(const int& p)
{
    if(!isValidPos(p))
    {
        throw ListException("Posicion Invalida, retrieve");
    }
    return data[p];
}

template <class T,int arraysize>
string List<T,arraysize>::toString()
{
    string result;

    int i(0);
    while(i <= last)
    {
        result += data[i].toString() + "/n";
        i++;
    }

    return result;
}

template <class T,int arraysize>
void List<T,arraysize>::deleteAll()
{
    last = -1;
}

template <class T,int arraysize>
List<T, arraysize>& List<T,arraysize>::operator = (const List<T,arraysize>& l)
{
    copyAll(l);

    return *this;
}
