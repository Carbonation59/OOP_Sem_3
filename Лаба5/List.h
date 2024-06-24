#define LIST3_H

using namespace std;

#include "Iterator.h"
#include "Trapezoid.h"
#include "Trapezoid.cpp"
#include <memory>

template<typename T>
class List{
private:
        shared_ptr<T*> buf = make_shared<T*>(new T[2]);
        size_t sz = 0;
        size_t cap = 2;
public:
        friend class Iterator<T>;
        List();
        List(size_t n, const T& value = T());
        List(const List<T>& orig);
        size_t size();
        size_t capacity();
        void reserve(size_t n);
        void resize(size_t n, const T& value = T());
        void push_back(const T& value = T());
        void pop_back();
        bool empty();
        T* data();
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;
        T& operator[](size_t i);
        const T& operator[](size_t i) const;
        T& at(size_t i);
        const T& at(size_t i) const;
        Iterator<T> begin();
        Iterator<T> end();
        void insert(Iterator<T> pos, const T& value);
        void erase(Iterator<T> pos);
        ~List();
};

#endif








