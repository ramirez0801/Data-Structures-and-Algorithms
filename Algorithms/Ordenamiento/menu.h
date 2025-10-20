#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "list.h"
#include<random>
#include<chrono>
#include<functional>

class Menu
{
    private:
        void userInterface(List<int>&);
    public:
        Menu(List<int>&);
};
#endif


Menu::Menu(List<int> &myList)
{
    userInterface(myList);
}

void Menu::userInterface(List<int> &myList)
{
    /*int myT;
    string str;
    char op;
    int pos;*/
    default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> distribution(111111,999999);
    auto dice = bind(distribution,generator);
    int value;
    //cout<<"Leyendo del disco..."<<endl;
    //myList.readFromDisk("../prueba");
    cout<<"Llenando lista"<<endl;
    for(int i(0); i<20000; i++)
    {
        myList.insertData(myList.getLast(),dice());
    }
    
    cout<<"Listado:"<<endl;
    cout<<myList.toString();
    cout<<endl;

    cout<<"Ordenando..."<<endl;
    myList.sortDataQuick();

    cout<<"\nListado:"<<endl;
    cout<<myList.toString();

    cout<<"\nGuardado..."<<endl;
    myList.writeToDisk("../pruebaOrdenada");

}