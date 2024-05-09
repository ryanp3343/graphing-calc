#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "listfunctions.h"

template <class T>
class Queue {
public:
    class Iterator {
    public:
        explicit Iterator(node<T>* p = nullptr) : _ptr(p) {}

        Iterator& operator++() {
            if (_ptr) _ptr = _ptr->_next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        T& operator*() const {
            return _ptr->_item;
        }

        node<T>* operator->() const {
            return _ptr;
        }

        bool is_null() const {
            return !_ptr;
        }

        friend bool operator!=(const Iterator& left, const Iterator& right) {
            return left._ptr != right._ptr;
        }

        friend bool operator==(const Iterator& left, const Iterator& right) {
            return left._ptr == right._ptr;
        }

    private:
        node<T>* _ptr;
    };

    Queue();
    ~Queue();
    Queue(const Queue<T>& copyThis);
    Queue& operator=(const Queue& RHS);

    void push(const T& item);
    T pop();
    bool empty() const;
    Iterator Begin() const;
    Iterator End() const;
    void Print() const;

    friend std::ostream& operator<<(std::ostream& outs, const Queue<T>& l) {
        for (node<T>* ptr = l._head_ptr; ptr != nullptr; ptr = ptr->_next) {
            outs << "[" << ptr->_item << "]->";
        }
        outs << "|||" << std::endl;
        return outs;
    }

private:
    node<T>* _head_ptr;
    node<T>* _tail;
};

template <class T>
Queue<T>::Queue() : _head_ptr(nullptr), _tail(nullptr) {}

template <class T>
Queue<T>::~Queue() {
    // Delete the list
    DestroyList(_head_ptr);
    _tail = nullptr;
}

template <class T>
Queue<T>::Queue(const Queue<T>& copyThis) {
    // Copy the list using list functions
    _head_ptr = CopyList(copyThis._head_ptr);
    _tail = LastNode(_head_ptr);
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue& RHS) {
    if (this != &RHS) {
        DestroyList(_head_ptr);
        _head_ptr = CopyList(RHS._head_ptr);
        _tail = LastNode(_head_ptr);
    }
    return *this;
}

template <class T>
void Queue<T>::push(const T& item) {
    if (!_head_ptr) {
        _head_ptr = insertHead(_head_ptr, item);
        _tail = _head_ptr;
    }
    else {
        _tail = InsertAfter(_head_ptr, _tail, item);
    }
}

template <class T>
T Queue<T>::pop() {
    if (!_head_ptr) {
        throw std::runtime_error("Queue is empty, cannot pop");
    }

    T result = DeleteHead(_head_ptr);

    // Update tail pointer if the queue is empty after popping
    if (!_head_ptr) {
        _tail = nullptr;
    }

    return result;
}

template <class T>
bool Queue<T>::empty() const {
    return !_head_ptr;
}

template <class T>
typename Queue<T>::Iterator Queue<T>::Begin() const {
    return Iterator(_head_ptr);
}

template <class T>
typename Queue<T>::Iterator Queue<T>::End() const {
    return Iterator(nullptr);
}

template <class T>
void Queue<T>::Print() const {
    PrintList(_head_ptr);
}

#endif // QUEUE_H
