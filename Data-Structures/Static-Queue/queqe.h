
#include <exception>
#include <string>

class QuequeException : public std::exception
{
    private:
        std::string msg;
    
    public:
        explicit QuequeException(const char* message) : msg(message){ }

        explicit QuequeException(const std::string& message) : msg(message) { }

        virtual ~QuequeException() throw() {}

        virtual const char* what() throw() {
            return msg.c_str();
        }
};

template <class T,int ARRAYSIZE = 1024>
class Queue
{
    private:
        T data[ARRAYSIZE];
        int frontPOS;
        int endPOS;

        void copyAll(const Queue<T,ARRAYSIZE>&);

    public:
    Queue();
    Queue(const Queue<T,ARRAYSIZE>&);

        bool isEmpty();
        bool isFull();
        
        void enqueue(const T&);

        T dequeue();
        T getFront();

        Queue<T,ARRAYSIZE>& operator = (const Queue<T,ARRAYSIZE>&);
};

using namespace std;

template <class T,int ARRAYSIZE>
Queue<T,ARRAYSIZE>::Queue() : frontPOS(0), endPOS(ARRAYSIZE - 1){ }

template <class T,int ARRAYSIZE>
bool Queue<T,ARRAYSIZE>::isEmpty(){
    return frontPOS == endPOS + 1 or (frontPOS == 0 and endPOS == ARRAYSIZE - 1);
}

template <class T,int ARRAYSIZE>
bool Queue<T,ARRAYSIZE>::isFull(){
    return frontPOS == endPOS + 2 or (frontPOS == 0 and endPOS == ARRAYSIZE - 2)
        or (frontPOS == 1 and endPOS == ARRAYSIZE - 1);
}

template <class T,int ARRAYSIZE>
void Queue<T,ARRAYSIZE>::enqueue(const T& e){
    if(isFull())
    {
        throw QuequeException("Desbordamiento de datos. enqueue");
    }

    if(++endPOS == ARRAYSIZE)
        endPOS = 0;

    data[endPOS] = e;
}

template <class T,int ARRAYSIZE>
T Queue<T,ARRAYSIZE>::dequeue() {
    if(isEmpty())
        throw QuequeException("Cola vacia, dequeue");

    T result(data[frontPOS]);

    if(++frontPOS == ARRAYSIZE)
    {
        frontPOS = 0;
    }

    return result;
}

template <class T,int ARRAYSIZE>
T Queue<T,ARRAYSIZE>::getFront(){
    if(isEmpty())
        throw QuequeException("Insuficencia de datos, getFront");

    return data[frontPOS];
}

template <class T,int ARRAYSIZE>
Queue<T,ARRAYSIZE>& Queue<T,ARRAYSIZE>::operator = (const Queue<T,ARRAYSIZE>& q){
    copyAll(q);

    return *this;
}

template <class T,int ARRAYSIZE>
Queue<T,ARRAYSIZE>::Queue(const Queue<T,ARRAYSIZE>& q) {
    copyAll(q);
}

template <class T,int ARRAYSIZE>
void Queue<T,ARRAYSIZE>::copyAll(const Queue<T, ARRAYSIZE>& q)
{
    int i(0);
    while(i < q.endPOS)
    {
        data[i] = q.data[i];
        i++;
    }

    frontPOS = q.frontPOS;
    endPOS = q.endPOS;
}