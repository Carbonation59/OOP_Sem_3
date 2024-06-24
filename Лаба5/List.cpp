#include <cstddef>
#include <iostream>
#include <cstdlib>
#include "List.h"
#include "Trapezoid.h"
using namespace std;

template<typename T>
List<T>::List(){}

template <typename T>
List<T>::List(size_t n, const T& value){
        resize(n, value);
}

template <typename T>
List<T>::List(const List<T>& orig){
        buf = orig.data();
        sz = orig.size();
        cap = orig.capacity();
}

template <typename T>
size_t List<T>::size(){
        return sz;
}

template <typename T>
size_t List<T>::capacity(){
        return cap;
}

template <typename T>
void List<T>::reserve(size_t n){
        if(n <= cap) return;
        T* newbuf = new T[n];
        //cout << newbuf << " " << sz << endl;
        for(size_t i = 0; i < sz; ++i){
                //cout << i << endl;
                newbuf[i] = at(i);
        }
        delete[] (*buf.get());
        buf = make_shared<T*>(newbuf);
        cap = n;
}

template <typename T>
void List<T>::resize(size_t n, const T& value){
        if(n > cap) reserve(n);
        size_t i = sz;
        try{
                for(size_t i = sz; i < n; ++i){
                        new (*buf.get() + i) T(value);
                }
        } catch(...){
                for(size_t j = sz; j < i; ++j){
                        (*buf.get() + j)->~T();
                }
                throw;
        }
        if(n < sz) sz = n;
}

template <typename T>
void List<T>::push_back(const T& value){
        insert(end(), value);
        /*if(cap == sz){
                resize(2 * cap);
        }
        new (*buf.get() + sz) T(value);
        ++sz;*/
}

template <typename T>
void List<T>::pop_back(){
        --sz;
        (buf.get() + sz)->~T();
}

template <typename T>
bool List<T>::empty(){
        return sz == 0;
}

template <typename T>
T* List<T>::data(){
        return (*buf.get());
}

template <typename T>
T& List<T>::front(){
        if(empty()){
                throw out_of_range("List is empty!");
        }
        return (*buf.get())[0];
}

template <typename T>
const T& List<T>::front() const{
        if(empty()){
                throw out_of_range("List is empty!");
        }
        return (*buf.get())[0];
}

template <typename T>
T& List<T>::back(){
        if(empty()){
                throw out_of_range("List is empty!");
        }
        return (*buf.get())[sz-1];
}

template <typename T>
const T& List<T>::back() const{
        if(empty()){
                throw out_of_range("List is empty!");
        }
        return (*buf.get())[sz-1];
}

template <typename T>
T& List<T>::operator[](size_t i){
        return (*buf.get())[i];
}

template <typename T>
const T& List<T>::operator[](size_t i) const{
        return (*buf.get())[i];
}

template <typename T>
T& List<T>::at(size_t i){
        if(i >= sz){
                throw out_of_range("Wrong index in List!");
        }
        return (*buf.get())[i];
}

template <typename T>
const T& List<T>::at(size_t i) const{
        if(i >= sz){
                throw out_of_range("Wrong index in List!");
        }
        return (*buf.get())[i];
}

template <typename T>
Iterator<T> List<T>::begin(){
        return Iterator<T>(*buf.get(), 0);
}

template <typename T>
Iterator<T> List<T>::end(){
        return Iterator<T>(*buf.get() + sz, sz);
}

template <typename T>
void List<T>::insert(Iterator<T> pos, const T& value){
        if((pos < begin()) || (pos > end())){
                throw out_of_range("Wrong iterator!");
        }
        if(sz == cap){
                resize(2 * cap);
        }
        pos = Iterator<T>(*buf.get() + pos.index(), pos.index());

        ++sz;
        if(pos == end() - 1){
        } else{
                Iterator<T> it = end();
                for(; it != pos; --it){
                        new (it.base()) T(*(it - 1));
                        //*it = Trapezoid<T>(*(it - 1));
                        //cout << *it << " " << *(it - 1) << endl;
                }
        }
        new(pos.base()) T(value);
}

template <typename T>
void List<T>::erase(Iterator<T> pos){
        if((pos < begin()) || (pos >= end()) || empty()){
                throw out_of_range("Wrong iterator!");
        }
        for(Iterator<T> it = pos; it != end(); ++it){
                *it = *(it + 1);
        }
        --sz;
}

template <typename T>
List<T>::~List(){
        for(size_t i = 0; i < sz; ++i){
                (*buf.get() + i)->~T();
        }
        delete[] (*buf.get());
}


