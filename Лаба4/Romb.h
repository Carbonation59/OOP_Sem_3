#ifndef RECTANGLE_H
#define 	RECTANGLE_H
#include <cstdlib>
#include <iostream>
 
class Rectangle {
public:
	Rectangle(double i,double j);
	Rectangle();
	Rectangle(const Rectangle& orig);
	double square();
	void print_points();
	void print_sides();
	friend std::ostream& operator<<(std::ostream& os, Rectangle& obj);
	friend std::istream& operator>>(std::istream& is,  Rectangle& obj);
	bool operator==(Rectangle& copy);
	Rectangle& operator=(const Rectangle& copy);
	virtual ~Rectangle();
private:
	double one;
	double two;
};
 
#endif 