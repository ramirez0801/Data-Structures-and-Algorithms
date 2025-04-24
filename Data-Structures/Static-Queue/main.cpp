#include<iostream>
#include<random>
#include<chrono>
#include<functional>

#include "queqe.h"
using namespace std;

int main()
{
    default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> distribution(111,999);
    auto dice = bind(distribution,generator);

    Queue<int> myCola;
    int value;

    for(int i(0); i<20; i++)
    {
        value = dice(0);

        cout<<"Encolando: "<<value<<endl;

        myCola.enqueue(value);
    }

    cout<<endl<<endl;

    cout <<"Contenido: "<<endl;

    while(!myCola.isEmpty())
    {
        cout<<myCola.dequeue()<<endl;
    }

    cout<<endl;

    return 0;
}
