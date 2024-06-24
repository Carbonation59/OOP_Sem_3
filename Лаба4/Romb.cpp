#include "Rectangle.h"
#include <iostream>
#include <cmath>

using namespace std;
 
 
Rectangle::Rectangle(double i, double j) : one(i), two(j) {
}

Rectangle::Rectangle() : one(0), two(0) {
}
 
Rectangle::Rectangle(const Rectangle& orig) {
	one = orig.one;
	two = orig.two;
}
 
double Rectangle::square(){
 	return one*two;
}

void Rectangle::print_points(){
	cout << "(" << one/2 << ";" << two/2 << "), ";
	cout << "(" << one/2 << ";" << two/2*(-1) << "), ";
	cout << "(" << one/2*(-1) << ";" << two/2*(-1) << "), ";
	cout << "(" << (one/2)*(-1) << ";" << two/2 << ")";
}

void Rectangle::print_sides{
	cout << one << ", " << two << "\n";
}

bool Rectangle::operator==(Rectangle& copy) {
	if (one == copy.one && two == copy.two){
		return true;
	} else {
		return false;
	}
}
 
Rectangle& Rectangle::operator=(const Rectangle& copy) {
	if (this == &copy) return *this;
	one = copy.one;
	two = copy.two;
	return *this;
}

Rectangle::~Rectangle() {
}
 
std::ostream& operator<<(std::ostream& os, Rectangle& obj) {
	os << "Points: ";
	obj.print_points();
	os << "\nBase 1:" << one;
	os << "\nBase 2:" << two;
	os << "\nEdge: " << sqrt((two-one)/2*three);
	os << "\n" << "Square: "<< obj.square();
	return os;
}
 
std::istream& operator>>(std::istream& is, Rectangle& obj) {
	if(!(is >> obj.one >> obj.two)){
                throw invalid_argument("Wrong values!");
    }
	return is;
}
