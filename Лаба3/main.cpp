// Почечура Артемий Андреевич

// М8О-206Б-20

// Лабораторная работа №3

// Вариант 12: Разработать классы согласно варианту задания, классы должны  наследоваться от базового класса Figure. Фигуры: трапеция, ромб, пятиугольник.


#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <stack>
#include <set>
 
using namespace std;

double koef_nakl(pair<double,double> a, pair<double,double> b) {
	double k = (a.second - b.second) / (a.first - b.first);
	return k;
}

bool trapezoid_check(pair<double,double> a, pair<double,double> b, pair<double,double> c, pair<double,double> d) {
	double Area= (a.first*b.second+b.first*c.second+c.first*d.second+d.first*a.second-
			a.second*b.first-b.second*c.first-c.second*d.first-d.second*a.first)/2;
	if (Area == 0) {
		return false;
	}
	if (koef_nakl(a, b) == koef_nakl(c, d)) { return true; }
	else if (koef_nakl(b, c) == koef_nakl(a, d)) { return true; }
	return false;
}

bool rhombus_check(pair<double,double> a, pair<double,double> b, pair<double,double> c, pair<double,double> d) {
	double Area= (a.first*b.second+b.first*c.second+c.first*d.second+d.first*a.second-
			a.second*b.first-b.second*c.first-c.second*d.first-d.second*a.first)/2;
	if (Area == 0) {
		return false;
	}
	if (koef_nakl(a, b) == koef_nakl(c, d) && ((a.first*-b.first)*(a.first*-b.first)+(a.second*-b.second))==((c.first*-d.first)*(c.first*-d.first)+(c.second*-d.second))) { return true; }
	else if (koef_nakl(b, c) == koef_nakl(a, d) && ((b.first*-c.first)*(b.first*-c.first)+(b.second*-c.second))==((a.first*-d.first)*(a.first*-d.first)+(a.second*-d.second))) { return true; }
	return false;
}


long long cross(pair<double,double> a, pair<double,double> b) {
	return a.first * b.second - a.second * b.first;
}

bool operator < (pair<double,double> a, pair<double,double> b) {
	return cross(a, b) < 0;
}

class Figure{
public:
	virtual double area()=0;
	virtual pair<double, double> centre()=0;
	virtual bool select()=0;
	virtual void print()=0;
	virtual ~Figure(){}
};

class Trapezoid: public Figure{
	pair<double,double> v[4];
public:
	bool select(){
		for(int i=0;i<4;i++){
			cin >> v[i].first >> v[i].second;
		}
		if(!trapezoid_check(v[0],v[1],v[2],v[3])){
				return false;
		} 
		return true;
	}
	void print(){
		for(int i=0;i<4;i++){
			cout << v[i].first << " " << v[i].second << "\n";
		}
	}
	pair<double, double> centre(){
		pair<double, double> a;
		a.first=0;
		a.second=0;
		for(int i=0;i<4;i++){
			a.first=a.first+v[i].first;
			a.second=a.second+v[i].second;
		}
		a.first=a.first/4;
		a.second=a.second/4;
		return a;
	}
	double area(){
		return abs(v[0].first*v[1].second+v[1].first*v[2].second+v[2].first*v[3].second+v[3].first*v[0].second-
			v[0].second*v[1].first-v[1].second*v[2].first-v[2].second*v[3].first-v[3].second*v[0].first)/2;
	}
	~Trapezoid(){};
};

class Rhombus: public Figure{
	pair<double, double> v[4];
public:
	bool select(){
		for(int i=0;i<4;i++){
			cin >> v[i].first >> v[i].second;
		}
		if(!rhombus_check(v[0],v[1],v[2],v[3])){
				return false;
		} 
		return true;
	}
	void print(){
		for(int i=0;i<4;i++){
			cout << v[i].first << " " << v[i].second << "\n";
		}
	}
	pair<double, double> centre(){
		pair<double, double> a;
		a.first=0;
		a.second=0;
		for(int i=0;i<4;i++){
			a.first=a.first+v[i].first;
			a.second=a.second+v[i].second;
		}
		a.first=a.first/4;
		a.second=a.second/4;
		return a;
	}
	double area(){
		return abs(v[0].first*v[1].second+v[1].first*v[2].second+v[2].first*v[3].second+v[3].first*v[0].second-
			v[0].second*v[1].first-v[1].second*v[2].first-v[2].second*v[3].first-v[3].second*v[0].first)/2;
	}
	~Rhombus(){};
};

class Pentagon: public Figure{
	pair<double, double> v[5];
public:
	bool select(){
		for(int i=0;i<5;i++){
			cin >> v[i].first >> v[i].second;
		}
		for(int i = 0; i < 5; i++){
			if(v[i] < v[(i+1)%5]){
				return false;
			}
		}
		for(int i = 0; i < 5; i++){
			double h=acos((v[(i+1)%5].first-v[i].first)*(v[(i+2)%5].first-v[(i+1)%5].first)+(v[(i+1)%5].second-v[i].second)*(v[(i+2)%5].second-v[(i+1)%5].second));
			if(h!=0,942){
				return false;
			}
		}
		return true;
	}
	void print(){
		for(int i=0;i<5;i++){
			cout << v[i].first << " " << v[i].second << "\n";
		}
	}
	pair<double, double> centre(){
		pair<double, double> a;
		a.first=0;
		a.second=0;
		for(int i=0;i<4;i++){
			a.first=a.first+v[i].first;
			a.second=a.second+v[i].second;
		}
		a.first=a.first/4;
		a.second=a.second/4;
		return a;
	}
	double area(){
		return abs(v[0].first*v[1].second+v[1].first*v[2].second+v[2].first*v[3].second+v[3].first*v[4].second+v[4].first*v[0].second-
			v[0].second*v[1].first-v[1].second*v[2].first-v[2].second*v[3].first-v[3].second*v[4].first-v[4].second*v[0].first)/2;
	}
	~Pentagon(){};
};


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << "0 - exit\n";
	cout << "1 - select a trapezoid\n";
	cout << "2 - select a rhombus\n";
	cout << "3 - select a pentagon\n";
	cout << "4 - delete an element of vector\n";
	cout << "5 - print centre, square and points of each figure of vector\n";
	vector<Figure*> v;
	int n=50;
	while(n!=0){
		if(!(cin >> n)){
			cout << "Wrong values\n";
			for(int i=0;i<v.size();i++){
				delete v[i];
			}
			return 0;
		} else if(n==1){
			Figure *A=new Trapezoid;
			if(!(*A).select()){
				cout << "Wrong selection\n";
				return 0;
			}
			v.push_back(A);
		} else if(n==2) {
			Figure *A=new Rhombus;
			if(!(*A).select()){
				cout << "Wrong selection\n";
				return 0;
			}
			v.push_back(A);
		} else if(n==3){
			Figure *A=new Pentagon;
			if(!(*A).select()){
				cout << "Wrong selection\n";
				return 0;
			}
			v.push_back(A);
		} else if(n==4){
			if(v.size()!=0){
				int i;
				cout << "select a position\n";
				cin >> i;
				v.erase(v.begin()+i-1);
			} else {
				cout << "vector is empty\n";
			}
		} else if(n==5){
			for(int i=0;i<v.size();i++){
				pair<double, double> a=(*v[i]).centre();
				cout << "centre: " << a.first << " " << a.second << "\n" << "area: " << (*v[i]).area() << "\n" << "points of figure:\n";
				(*v[i]).print();
			}
		}
	}
	for(int i=0;i<v.size();i++){
			delete v[i];
	}
	return 0;
}