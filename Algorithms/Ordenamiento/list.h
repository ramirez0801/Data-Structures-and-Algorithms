
#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <iostream>
#include <fstream>

#include "exception.h"

template <class T, int ARRAYSIZE = 20000>
class List
{
    private:
        T data[ARRAYSIZE];
        int last;

        void swapData(T&,T&);
        bool isValidPos(const int&);
        void copyAll(const List<T,ARRAYSIZE> &);

        void sortDataMerge(const int&, const int&);
        void sortDataQuick(const int&, const int&);
    
    public:
        List();
        List(const List<T,ARRAYSIZE>&);
    
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

        void sortBubble();
        void sortShell();
        void sortInsert();
        void sortSelect();

        void sortDataMerge();
        void sortDataQuick();

        void writeToDisk(const std::string&);
        void readFromDisk(const std::string&);

        void deleteAll();

        List<T, ARRAYSIZE>& operator = (const List<T,ARRAYSIZE>&);
};

using namespace std;

template <class T,int ARRAYSIZE>
void List<T,ARRAYSIZE>::copyAll(const List<T,ARRAYSIZE>& l)
{
    int i(0);
    while(i <= l.last)
    {
        data[i] == l.data[i];
        i++;
    }

    last = l.last;
}

template <class T,int ARRAYSIZE>
bool List<T,ARRAYSIZE>::isValidPos(const int& p)
{
    return p >= 0 or p <=last;
}

template <class T,int ARRAYSIZE>
List<T,ARRAYSIZE>::List() : last(-1) { }

template <class T,int ARRAYSIZE>
List<T,ARRAYSIZE>::List(const List<T,ARRAYSIZE>& l)
{
    copyAll(l);
}

template <class T,int ARRAYSIZE>
bool List<T,ARRAYSIZE>::isEmpty()
{
    return last == -1;
}

template <class T,int ARRAYSIZE>
bool List<T,ARRAYSIZE>::isFull()
{
    return last == ARRAYSIZE - 1;
}


template <class T,int ARRAYSIZE>
void List<T,ARRAYSIZE>::insertData(const int& p, const T& e)
{
    if(isFull())
    {
        throw ListException("Desbordamiento, insertData");
    }

    if(!isValidPos(p))
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

template <class T,int ARRAYSIZE>
void List<T,ARRAYSIZE>::deleteData(const int& p)
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

template <class T,int ARRAYSIZE>
int List<T,ARRAYSIZE>::getFirst()
{
    if(isEmpty())
    {
        return -1;
    }

    return 0;
}

template <class T,int ARRAYSIZE>
int List<T,ARRAYSIZE>::getLast()
{
    return last;
}

template <class T,int ARRAYSIZE>
int List<T,ARRAYSIZE>::getPrevPos(const int& p)
{
    if(p == getFirst() or !isValidPos(p))
    {
        return -1;
    }

    return p - 1;
}

template <class T,int ARRAYSIZE>
int List<T,ARRAYSIZE>::getNextPos(const int& p)
{
    if(p == getLast() or !isValidPos(p))
    {
        return -1;
    }

    return p + 1; 
}

template <class T,int ARRAYSIZE>
T List<T,ARRAYSIZE>::retrieve(const int& p)
{
    if(!isValidPos(p))
    {
        throw ListException("Posicion Invalida, retrieve");
    }
    return data[p];
}

template <class T,int ARRAYSIZE>
string List<T,ARRAYSIZE>::toString()
{
    string result;
    int i(0);
    while(i <= last)
    {
        result += to_string(data[i]) + ",";
        i++;
    }

    return result;
}

template <class T,int ARRAYSIZE>
void List<T,ARRAYSIZE>::deleteAll()
{
    last = -1;
}

template <class T,int ARRAYSIZE>
List<T, ARRAYSIZE>& List<T,ARRAYSIZE>::operator = (const List<T,ARRAYSIZE>& l)
{
    copyAll(l);

    return *this;
}


template <class T,int ARRAYSIZE>
void List<T,ARRAYSIZE>::writeToDisk(const string& fileName)
{
    ofstream myFile;
    myFile.open(fileName, ios_base::trunc);

    if(!myFile.is_open())
    {
        throw ListException("No se abrio el archivo, Write");
    }

    int i(0);

    while(i <=last)
    {
        myFile << data[i++] << endl;
    }

    myFile.close();
}

template <class T,int ARRAYSIZE>
void List<T,ARRAYSIZE>::readFromDisk(const string &fileName)
{
    ifstream myFile;
    T myData;

    myFile.open(fileName);

    if(!myFile.is_open()){
        throw ListException("No se pudo abrir el archivo, Read");
    }

    last = -1;

    while(myFile >> myData){
        data[++last] = myData;
    }

    myFile.close();
}

template <class T,int ARRAYSIZE>
void List<T,ARRAYSIZE>::swapData(T& a ,T& b)
{
    T aux(a);
    a = b;
    b = aux;
}

template <class T,int ARRAYSIZE>
void List<T,ARRAYSIZE>::sortBubble()
{
    int i(last),j;
    bool flag;

    do
    {
        flag = false;
        j = 0;
        while(j < i)
        {
            if(data[j] > data[j+1])
            {
                swapData(data[j], data[j+1]);
                flag = true;
            }
            j++;
        }
        i--;
    }while(flag);
}

template <class T,int ARRAYSIZE>
void List<T,ARRAYSIZE>::sortInsert()
{
    int i(1),j;
    T aux;

    while(i <= last)
    {
        aux = data[i];
        j = i;

        while(j > 0 && aux < data[j-1])
        {
            data[j] = data[j-1];
            j--;
        }

        if(i != j)
        {
            data[j] = aux;
        }

        i++;
    }
}

template <class T,int ARRAYSIZE>
void List<T,ARRAYSIZE>::sortSelect()
{
    int i(0),j,m;

    while(i < last)
    {
        m = i;
        j = i + 1;
        
        while(j <= last)
        {
            if(data[j] < data[m])
            {
                m = j;
            }

            j++;
        }

        if(i != m)
        {
            swap(data[i], data[m]);
        }

        i++;
    }
}

template <class T,int ARRAYSIZE>
void List<T,ARRAYSIZE>::sortShell()
{
    float factor(1.0/2.0);
    int dif((last + 1) * factor),i,j;

    while(dif > 0)
    {
        i = dif;
        while(i <= last)
        {
            j = i;
            while(j >= dif && data[j - dif] > data[j])
            {
                swapData(data[j - dif], data[j]);
                j -= dif;
            }
            i++;
        }
        dif *= factor;
    }
}

template <class T,int ARRAYSIZE>
void List<T,ARRAYSIZE>::sortDataMerge()
{
    sortDataMerge(0,last);
}

template <class T,int ARRAYSIZE>
void List<T,ARRAYSIZE>::sortDataMerge(const int& leftEdge, const int& rightEdge)
{
    if(leftEdge >= rightEdge)
        return;
    
    int m((leftEdge + rightEdge) /2);

    sortDataMerge(leftEdge,m);
    sortDataMerge(m+1,rightEdge);

    static T aux[ARRAYSIZE];
    for(int n(leftEdge); n <= rightEdge; n++)
    {
        aux[n] = data[n];
    }

    int i(leftEdge), j(m+1), x(leftEdge);

    while(i<=m and j <= rightEdge)
    {
        while(i <= m and aux[i] <= aux[j])
        {
            data[x++] = aux[i++];
        }

        if(i <= m)
        {
            while(j <= rightEdge and aux[j] <= aux[i])
            {
                data[x++] = aux[j++];
            }
        }
    }

    while(i<=m)
        data[x++] = aux[i++];
    
    while(j<=rightEdge)
        data[x++] = aux[j++];
}

template <class T,int ARRAYSIZE>
void List<T,ARRAYSIZE>::sortDataQuick()
{
    sortDataQuick(0,last);
}

template <class T,int ARRAYSIZE>
void List<T,ARRAYSIZE>::sortDataQuick(const int& leftEdge, const int& rightEdge)
{
    if(leftEdge >= rightEdge)
        return;

    int i(leftEdge), j(rightEdge);
    while(i<j)
    {
        while(i<j and data[i] <= data[rightEdge])
            i++;
        while(i<j and data[j] >= data[rightEdge])
            j--;
        if(i!=j)
            swapData(data[i],data[j]);
    }
    if(i!=rightEdge)
        swapData(data[i],data[rightEdge]);

    sortDataQuick(leftEdge,i-1);
    sortDataQuick(i+1,rightEdge);
}

#endif