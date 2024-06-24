#define ITERATOR_H

#include <memory>
#include "Trapezoid.h"
using namespace std;

template <typename T>
class Iterator{
private:
        T* ptr= nullptr;
        size_t idx = -1;
public:
        typedef std::random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef T difference_type;
        typedef T* pointer;
        typedef T& reference;
        Iterator();
        Iterator(T* t, size_t idx);
        Iterator& operator+=(size_t n);
        Iterator& operator-=(size_t n);
        Iterator operator+(size_t n);
        Iterator operator-(size_t n);
        T* base() const;
        size_t index() const;
        T& operator*();
        Iterator* operator->();
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
        bool operator==(Iterator const& other) const;
        bool operator!=(Iterator const& other) const;
        template <typename V> friend bool operator==(const Iterator<V>& lhs, const Iterator<V>& rhs);
        template <typename V> friend bool operator!=(const Iterator<V>& lhs, const Iterator<V>& rhs);
        template <typename V> friend bool operator<(const Iterator<V>& lhs, const Iterator<V>& rhs);
        template <typename V> friend bool operator>(const Iterator<V>& lhs, const Iterator<V>& rhs);
        template <typename V> friend bool operator<=(const Iterator<V>& lhs, const Iterator<V>& rhs);
        template <typename V> friend bool operator>=(const Iterator<V>& lhs, const Iterator<V>& rhs);
        template <typename V> friend size_t operator-(const Iterator<V>& lhs, const Iterator<V>& rhs);
        template <typename V> friend Iterator operator+(size_t n, const Iterator<V>& i);
        Iterator& operator=(const Iterator& copy);
};

#endif

