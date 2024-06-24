#include <cstddef>
#include "Iterator.h"
#include "Trapezoid.h"
using namespace std;

template <typename T>
Iterator<T>::Iterator() : ptr(nullptr){}

template <typename T>
Iterator<T>::Iterator(T* t, size_t index) : ptr(t), idx(index){}

template <typename T>
Iterator<T>& Iterator<T>::operator+=(size_t n){
        ptr += n;
        idx += n;
        return *this;
}

template <typename T>
Iterator<T>& Iterator<T>::operator-=(size_t n){
        ptr -= n;
        idx -= n;
        return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator+(size_t n){
        auto copy = *this;
        copy += n;
        return copy;
}

template <typename T>
Iterator<T> Iterator<T>::operator-(size_t n){
        auto copy = *this;
        copy -= n;
        return copy;
}

template <typename T>
T* Iterator<T>::base() const{
        return ptr;
}

template <typename T>
size_t Iterator<T>::index() const{
        return idx;
}

template <typename T>
T& Iterator<T>::operator*(){
        return *ptr;
}

template <typename T>
Iterator<T>* Iterator<T>::operator->(){
        return ptr;
}

template <typename T>
Iterator<T>& Iterator<T>::operator++(){
        ++ptr;
        ++idx;
        return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator++(int){
        auto copy = *this;
        copy++;
        return copy;
}

template <typename T>
Iterator<T>& Iterator<T>::operator--(){
        --ptr;
        --idx;
        return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator--(int){
        auto copy = *this;
        copy--;
        return copy;
}

template <typename T>
bool Iterator<T>::operator==(Iterator const& other) const{
        return ptr == other.base() && idx == other.index();
}

template <typename T>
bool Iterator<T>::operator!=(Iterator const& other) const{
        return ptr != other.base() || idx != other.index();
}

template <typename T>
bool operator==(const Iterator<T>& lhs, const Iterator<T>& rhs){
        return lhs.base() == rhs.base() && lhs.index() == rhs.index();
}

template <typename T>
bool operator!=(const Iterator<T>& lhs, const Iterator<T>& rhs){
        return lhs.base() != rhs.base() || lhs.index() != rhs.index();
}

template <typename T>
bool operator<(const Iterator<T>& lhs, const Iterator<T>& rhs){
        return lhs.base() < rhs.base() && lhs.index() == rhs.index();
}

template <typename T>
bool operator>(const Iterator<T>& lhs, const Iterator<T>& rhs){
        return lhs.base() > rhs.base();
}

template <typename T>
bool operator<=(const Iterator<T>& lhs, const Iterator<T>& rhs){
        return lhs.base() <= rhs.base();
}

template <typename T>
bool operator>=(const Iterator<T>& lhs, const Iterator<T>& rhs){
        return lhs.base() >= rhs.base();
}

template <typename T>
size_t operator-(const Iterator<T>& lhs, const Iterator<T>& rhs){
        return lhs.base() - rhs.base();
}

template <typename T>
Iterator<T> operator+(size_t n, const Iterator<T>& i){
        return reinterpret_cast<T>(i.base() + n, i.index() + n);
}

template <typename T>
Iterator<T>& Iterator<T>::operator=(const Iterator& copy){
        ptr = copy.base();
        idx = copy.index();
        return *this;
}







