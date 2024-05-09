#ifndef STACK_H
#define STACK_H

#include "list.h"

template <class T>
class Stack {
public:
    class Iterator {
    public:
        Iterator(node<T>* p = nullptr) : _ptr(p) {}

        T& operator*() {
            return _ptr->_item;
        }

        node<T>* operator->() const {
            return _ptr;
        }

        Iterator& operator++() {
            _ptr = _ptr->_next;
            return *this;
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

    Stack() = default;
    ~Stack() = default;

    void push(const T& item) {
        stack.InsertHead(item);
    }

    T pop() {
        if (empty()) throw std::out_of_range("Stack underflow");
        node<T>* discard = stack.Begin();
        return stack.Delete(discard);
    }

    T top() const {
        if (empty()) throw std::out_of_range("Stack is empty");
        return stack.Begin()->_item;
    }

    bool empty() const {
        return stack.Begin() == nullptr;
    }

    Iterator begin() const {
        return Iterator(stack.Begin());
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

    void Print() const {
        stack.Print();
    }

    template <class U>
    friend std::ostream& operator<<(std::ostream& outs, const Stack<U>& l) {
        outs << "Stack Top->";
        typename Stack<U>::Iterator iter(l.begin());
        while (iter != l.end()) {
            outs << *iter << " ";
            ++iter;
        }
        outs << "|||" << std::endl;
        return outs;
    }

private:
    List<T> stack;
};

#endif // STACK_H
