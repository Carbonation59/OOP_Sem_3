// Почечура Артемий, гр. М8О-206Б-20
// ЛР №6, вариант 11
// Параметром шаблона должен являться скалярный тип данных задающий тип данных для оси координат.
// Классы должны иметь публичные поля. Фигура - прямоугольник.
// Для хранения координат фигур необходимо использовать шаблон  pair.
// Коллекция - список.
// Аллокатор - стек.
// Создать шаблон динамической коллекцию, согласно варианту задания:
/*      1.      Коллекция должна быть реализована с помощью умных указателей(shared_ptr, weak_ptr).Опционально использование unique_ptr.
        2.              В качестве параметра шаблона коллекция должна принимать тип данных.
        3.      Коллекция должна содержать метод доступа к элементу по оператору[].
        4.      Реализовать аллокатор, который выделяет фиксированный размер памяти(количество блоков памяти – является параметром шаблона аллокатора).Внутри аллокатор должен хранить указатель на используемый блок памяти и динамическую коллекцию указателей на свободные блоки.
        5.      Коллекция должна использовать аллокатор для выделения и освобождения памяти для своих элементов.
        6.      Аллокатор должен быть совместим с контейнерами map и list.
        7.      Реализовать программу, которая:
                o       позволяет вводить с клавиатуры фигуры(с типом int в качестве параметра шаблона фигуры) и добавлять в коллекцию использующую аллокатор;
                o       позволяет удалять элемент из коллекции по номеру элемента;
                o       выводит на экран введенные фигуры c помощью for_each. */

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iterator>
#include <algorithm>
#include <memory>
#include <exception>
#include <stdexcept>
#include <stack>
#include "Rectangle.h"
#include "Rectangle.cpp"


using namespace std;

template<class F, class T>
 class forward_iterator : public iterator<input_iterator_tag, F> {
 public:
        F* ptr;
        forward_iterator(F* pt) :ptr(pt) {}
        T& operator*() {
                return ptr->value;
        }
        T* operator->() const {
                return &ptr->value;
        }
        forward_iterator& operator++() {
                if (ptr == nullptr) {
                        throw runtime_error("Trying to increment null pointer");
                }
                if (ptr->next) {
                        ptr = ptr->next.get();
                }
                else {
                        ptr = nullptr;
                }
                return *this;
        }
        forward_iterator operator++(int) {
                auto res = *this;
                operator++();
                return res;
        }
        bool operator==(const forward_iterator& lval) const {
                return ptr == lval.ptr;
        }
        bool operator!=(const forward_iterator& lval) const {
                return ptr != lval.ptr;
        }
        operator bool() {
                return ptr;
        }
};

template <class T>
class my_allocator : public allocator<T> {
public:
        stack<T*> memory;
        T* allocate(size_t n) {
                for (int i = 0; i < n; i++) {
                        memory.push_back(new T);
                }
                return *prev(memory.end());
        }
        void deallocate(T* pointer, size_t) {
                auto it = find_if(memory.begin(), memory.end(), [pointer](const auto ptr) {return ptr == pointer; });
                if (it != memory.end()) {
                        delete (*it);
                        memory.erase(it);
                }
        }
        void destroy(T* p) {
                p->~T();
        }
};

template <class T, class Allocator = allocator<T>>
class List {
public:
        static Allocator get_allocator() {
                static Allocator allocator;
                return allocator;
        }
        struct list_item {
                T value = {};
                unique_ptr<list_item> next = nullptr;
                list_item() = default;
                list_item(T val) : value(move(val)) {}
                void* operator new(size_t size) {
                        return get_allocator().allocate(sizeof(T));
                }
                void operator delete(void* p) {
                //      get_allocator().destroy((T*)p);
                        get_allocator().deallocate((T*)p, sizeof(T));
                }
        };
        size_t size_;
        unique_ptr<list_item> head;
        using iterator = forward_iterator<list_item, T>;
        List() {
                size_ = 0;
                head = nullptr;
        }
        List(size_t size) {
                size_ = size;
                if (size == 0) {
                        return;
                }
                head = make_unique<list_item>();
                list_item* node = head.get();
                while (size-- > 1) {
                        node->next = make_unique<list_item>();
                        node = node->next.get();
                }
        }
        T& operator[](size_t index) {
                if (index >= size() || index < 0) {
                        throw out_of_range("Index is out of range");
                }
                list_item* node = head.get();
                for (int i = 0; i < index; i++) {
                        node = node->next.get();
                }
                return node->value;
        }
        size_t size() {
                return size_;
        }
        iterator begin() {
                return iterator(head.get());
        }
        iterator end() {
                return iterator{ nullptr };
        }
        iterator insert(iterator it, T val) {
                if (it == begin()) {
                        auto ptr = make_unique<list_item>(val);
                        ptr->next = move(head);
                        head = move(ptr);
                        ++size_;
                        return begin();
                }
                iterator prev = find_prev(it);
                auto ptr = make_unique<list_item>(val);
                ptr->next = move(prev.ptr->next);
                prev.ptr->next = move(ptr);
                ++size_;
                return ++prev;
        }
        iterator erase(iterator it) {
                if (size_ == 0) {
                        throw runtime_error("List empty before erase");
                }
                if (it == begin()) {
                        head = move(head->next);
                        size_--;
                        return begin();
                }
                iterator prev = find_prev(it);
                if (it.ptr) {
                        prev.ptr->next = move(it.ptr->next);
                }
                else {
                        throw runtime_error("Trying to remove element using invalid iterator");
                }
                iterator res{ prev.ptr };
                size_--;
                ++res;
                return res;
        }
        T& back() {
                if (size_ == 0) {
                        throw runtime_error("List is empty");
                }
                auto tmp = find_prev(end());
                return *tmp;
        }
        T& front() {
                if (size_ == 0) {
                        throw runtime_error("List is empty");
                }
                return *begin();
        }
        void pop_front() {
                if (size_ == 0) {
                        throw runtime_error("List empty before pop");
                }
                erase(begin());
        }
        void pop_back() {
                if (size_ == 0) {
                        throw runtime_error("List empty before pop");
                }
                auto tmp = find_prev(end());
                erase(tmp);
        }
        void push_front(T value) {
                insert(begin(), move(value));
        }
        void push_back(T value) {
                insert(end(), move(value));
        }
        iterator find_prev(iterator cur) {
                if (cur == begin()) {
                        throw runtime_error("There is no element before the first");
                }
                iterator prev = begin();
                for (iterator it = ++begin(); it != end(); ++it) {
                        if (it == cur) {
                                return prev;
                        }
                        prev = it;
                }
                if (cur == end()) {
                        return prev;
                }
                throw invalid_argument("It's not iterator from this List");
        }
};

template <class T, class Alloc>
void print(List<T, Alloc>& st) {
        for_each(st.begin(), st.end(), [](auto& el) {cout << el << "\n"; });
}

bool readnum(int& a){
        cin >> a;
        if (cin.fail()) {
                        cout <<"Incorrect input"<<'\n';
            cin.clear();
            cin.ignore(numeric_limits<int>::max(),'\n');
            return false;
    }
    return true;
}
void help(){
        cout << "Commands:\n";
        cout << "\tadd - add element with index.\n\tdelete - delete element with index.\n";
        cout << "\tprint - print list";
        cout << "\n\tget - print element with index";
        cout << "\n\tend - exit\n";
        cout << "\thelp\n\n";
        cout << "Sides of rectangle (centre of figure - point (0;0)).\n\n";
}


int main(int argc, char** argv) {
        List<Rectangle<double>> list;
        string act;
        help();
        while (1){
                try{
                        cout << "Select a function: ";
                        cin>>act;
                        if (act=="end"){
                                break;
                        }
                        else if (act == "add"){
                                int ind;
                                cout << "input index: ";
                                if (!readnum(ind)){
                                        continue;
                                }
                                cout << "input horisontal side and vartical side: ";
                                Rectangle<double> a;
                                if(!(cin>>a)){
                                        cout << "Wrong values!";
                                        continue;
                                }
                                auto it = list.begin();
                                for (int i = 0; i < ind; i++) {
                                        ++it;
                                }
                                list.insert(it, a);
                                cout << "Element added\n";
                        }
                        else if (act == "delete"){
                                int ind;
                                cout << "input index: ";
                                if (!readnum(ind)){
                                        continue;
                                }
                                auto it = list.begin();
                                for (int i = 0; i < ind; i++) {
                                        ++it;
                                }
                                list.erase(it);
                                cout << "Element deleted\n";
                        }
                        else if (act == "print"){
                                print(list);
                        }
                        else if (act == "get"){
                                int ind;
                                cout << "input index: ";
                                if (!readnum(ind)){
                                        continue;
                                }
                                list[ind].print_info();
                        }
                        else if (act == "help"){
                                help();
                        }
                        else {
                                cout << "Invalid function. Enter 'help' for help."<<'\n';
                        }
                }
                catch (invalid_argument& exp) {
                        cout << exp.what() << "\n";
                }
                catch (runtime_error& exp) {
                        cout << exp.what() << "\n";
                }
                catch (out_of_range& exp) {
                        cout << exp.what() << "\n";
                }
        }
}

