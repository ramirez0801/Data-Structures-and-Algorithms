#include <menu.h>

using namespace std;

Menu::Menu(List<T> &myList)
{
    userInterface(myList);
}

void Menu::userInterface(List<T> &myList)
{
    T myT;
    Name n;
    Date d;
    string str;
    char op;
    int pos;

    do
    {
        //operaciones con el objeto
        //atof(str.c_str())
        //bool operator ==(const T&) const;  bool T::operator(const T& s)const{ return code == s.code}
        cout<<"Nombre: ";
        getline(cin,str);
        myT.setName(str);
        myList.insertData(myList.getLast(), myT);
        cout<<"Insertar otro? (s/n)"<<endl;
        cin>>op;
        cin.ignore();
    }while(op == 's' || op == 'S');

}