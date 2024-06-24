#ifndef RECTANGLE_H
#define         RECTANGLE_H
#include <utility>

using namespace std;

template<typename T>
class Rectangle {
public:
        Rectangle(T i,T j);
        Rectangle();
        Rectangle(const Rectangle<T>& orig);
        double square();
        void print_points();
        void print_info();
        void print_sides();
        template<typename V>  friend std::ostream& operator<<(std::ostream& os, Rectangle<V>& obj);
        template<typename V>  friend std::istream& operator>>(std::istream& is,  Rectangle<V>& obj);
        bool operator==(Rectangle<T>& copy);
        Rectangle<T>& operator=(const Rectangle<T>& copy);
        virtual ~Rectangle();
private:
        T one;
        T two;
};

#endif







