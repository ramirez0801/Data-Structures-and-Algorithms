#include "list.h"
#include "menu.h"
#include<random>
#include<chrono>
#include<functional>

using namespace std; 

int main(){
    List<int> myList;
    Menu myMenu(myList);
    return 0;
}