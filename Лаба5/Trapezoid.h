#ifndef TRAPEZOID_H
#define         TRAPEZOID_H
#include <utility>

using namespace std;

template<typename T>
class Trapezoid {
public:
        Trapezoid(T i,T j, T k);
        Trapezoid();
        Trapezoid(const Trapezoid<T>& orig);
        double square();
        double edge();
        void print_points();
        void print_diagonals();
        void print_info();
        void print_base_and_height();
        template<typename V>  friend std::ostream& operator<<(std::ostream& os, Trapezoid<V>& obj);
        template<typename V>  friend std::istream& operator>>(std::istream& is,  Trapezoid<V>& obj);
        bool operator==(Trapezoid<T>& copy);
        Trapezoid<T>& operator=(const Trapezoid<T>& copy);
        virtual ~Trapezoid();
private:
        T one;
        T two;
        T three;
};

#endif






