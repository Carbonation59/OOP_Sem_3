// Почечура Артемий Андреевич

// М8О-206Б-20

// Лабораторная работа №4

// Cпроектировать и запрограммировать на языке C++ класс-контейнер первого уровня, содержащий ромб (Вариант 12, Лабораторная работа №3). 
// Cтруктура данных для контейнера: Вариант 19 - N-дерево.


#include <iostream>
#include <sstream>
#include <math.h>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <stack>
#include <set>
#include "T_NTree.h"

 
using namespace std;

void usage(){
        cout << "USAGE:\n\na <EL> <PATH> - add element on specified path.\n\nd <PATH> - delete element for specified path.\n\nExample for path: cbcc.\n";
        cout << "Example for el:\n\n";
		cout << "First diagonal(line x): 12\n";
		cout << "Second diagonal(line y): 15\n";
        cout << "\nP - print tree";
		cout << "\np <PATH> - print element on specified path";
		cout << "\ne - end\n";
		cout << "\nCentre of all figures - point (0;0)\n\n";
}


int main(int argc, char** argv) {
	T_NTree tree;
	usage();
	while(true){
		try{
			string s;
			getline(cin,s);
			istringstream iss(s);
			char a;
			iss >> a;
			if(a=='a'){
				string S="";
				Romb a;
				iss >> a;
				iss >> S;
				tree.insert(S,a);
				cout << "Element added\n";
			} else if(a=='d'){
				string S="";
				iss >> S;
				tree.delete_el(S); 
				cout << "Element deleted\n";
			} else if(a=='P'){
				cout << tree;
			} else if(a=='p'){
				string S="";
				iss >> S;
				if(tree.get_el(S)){
					cout << "Diagonals: ";
					((*tree.get_el(S)).get_value()).print_diagonals();
					cout << *tree.get_el(S); 
				}
			} else if(a=='e'){
				break;
			}else {
				throw invalid_argument("Wrong command!");
			}
		} catch(const invalid_argument &arg){ 
			cout << arg.what() << "\n";
		}
	}
	return 0;
}
