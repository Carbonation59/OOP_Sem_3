#include "Trapezoid.h"
#include <iostream>
#include <cmath>

using namespace std;

template<typename T>
Trapezoid<T>::Trapezoid(T i, T j, T k) : one(i), two(j), three(k) {
}

template<typename T>
Trapezoid<T>::Trapezoid() : one(0), two(0), three(0) {
}

template<typename T>
Trapezoid<T>::Trapezoid(const Trapezoid<T>& orig) {
        one = orig.one;
        two = orig.two;
        three = orig.three;
}

template<typename T>
double Trapezoid<T>::square(){
        return (one + two) * three / 2.0;
}

template<typename T>
void Trapezoid<T>::print_points(){
        cout << "(" << one/2 << ";" << three/2 << "), ";
        cout << "(" << two/2 << ";" << three/2*(-1) << "), ";
        cout << "(" << two/2*(-1) << ";" << three/2*(-1) << "), ";
        cout << "(" << (one/2)*(-1) << ";" << three/2 << ")";
}

template<typename T>
void Trapezoid<T>::print_base_and_height(){
        cout << one << ", " << two << ", " << three << "\n";
}

template<typename T>
bool Trapezoid<T>::operator==(Trapezoid<T>& copy) {
        if (one == copy.one && two == copy.two && three==copy.three){
                return true;
        } else {
                return false;
        }
}

template<typename T>
Trapezoid<T>& Trapezoid<T>::operator=(const Trapezoid<T>& copy) {
        if (this == &copy) return *this;
        one = copy.one;
        two = copy.two;
        three = copy.three;
        return *this;
}

template<typename T>
Trapezoid<T>::~Trapezoid() {
}

template<typename T>
double Trapezoid<T>::edge(){
        double a=sqrt(abs(two-one))/2*three;
        if(a==0){
                return three;
        } else {
                return a;
        }
}

template<typename T>
void Trapezoid<T>::print_info(){
        cout << "Points: ";
        print_points();
        cout << "\nBase 1: " << one;
        cout << "\nBase 2: " << two;
        cout << "\nEdge: " << edge();
        cout << "\n" << "Square: "<< square() << "\n";
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Trapezoid<T>& obj) {
        os << obj.one;
        os << " " << obj.two;
        os << " " << obj.three;
        return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, Trapezoid<T>& obj) {
        if(!(is >> obj.one >> obj.two >> obj.three)){
                throw invalid_argument("Wrong values!");
        }
        return is;
}




