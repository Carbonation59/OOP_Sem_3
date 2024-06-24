// Почечура Артемий Андреевич

// М8О-206Б-20

// Лабораторная работа №5

// Вариант 12
// Фигура: Трапеция
// Cтруктура данных для контейнера: список.

#include <iostream>
#include <exception>
#include <vector>
#include <utility>
#include <cmath>
#include <sstream>
#include <algorithm>
#include "Iterator.h"
#include "Trapezoid.h"
#include "Iterator.cpp"
#include "List3.h"
#include "List3.cpp"
using namespace std;


bool readnum(int& a){
        cin >> a;
        if (cin.fail()) {
                        cout <<"Incorrect input"<<'\n';
            cin.clear();
            cin.ignore(numeric_limits<int>::max(),'\n');
            return false;
    }
    return true;
}
void help(){
        cout << "Commands:\n";
        cout << "\tadd - add element with index.\n\tdelete - delete element with index.\n";
        cout << "\tprint - print list";
        cout << "\n\tget - print element with index";
        cout << "\n\tend - exit\n";
        cout << "\thelp\n\n";
        cout << "Section, that join middles of bases, belong to axis Y (centre of section - point (0;0)).\n\n";
}


int main(int argc, char** argv) {
        List<Trapezoid<double>> list;
        string act;
        help();
        while (1){
                try{
                        cout << "Select a command: ";
                        cin>>act;
                        if (act=="end"){
                                break;
                        }
                        else if (act == "add"){
                                int ind;
                                cout << "input index: ";
                                if (!readnum(ind)){
                                        continue;
                                }
                                cout << "input first base, second base and height: ";
                                Trapezoid<double> a;
                                if(!(cin>>a)){
                                        cout << "Wrong values!";
                                        continue;
                                }
                                list.insert(list.begin()+ind,a);
                                cout << "Element added\n";
                        }
                        else if (act == "delete"){
                                int ind;
                                cout << "input index: ";
                                if (!readnum(ind)){
                                        continue;
                                }
                                list.erase(list.begin() + ind);
                                cout << "Element deleted\n";
                        }
                        else if (act == "print"){
                                for(auto i : list){
                                        cout << i << endl;
                                }
                        }
                        else if (act == "get"){
                                int ind;
                                cout << "input index: ";
                                if (!readnum(ind)){
                                        continue;
                                }
                                Trapezoid<double> t = list.at(ind);
                                t.print_info();
                        }
                        else if (act == "help"){
                                help();
                        }
                        else {
                                cout << "Invalid function. Enter 'help' for help."<<'\n';
                        }
                } catch(const invalid_argument &arg){
                        cout << arg.what() << "\n";
                } catch(const out_of_range &arg){
                        cout << arg.what() << "\n";
                }
        }
}


