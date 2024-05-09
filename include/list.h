#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "listfunctions.h"

template <typename T>
class List {
public:
    class Iterator {
    public:
        // Constructors
        Iterator() : _ptr(nullptr) {}
        explicit Iterator(node<T>* tmp) : _ptr(tmp) {}

        // Iterator navigation
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

        friend bool operator!=(const Iterator& left, const Iterator& right) {
            return left._ptr != right._ptr;
        }

        friend bool operator==(const Iterator& left, const Iterator& right) {
            return left._ptr == right._ptr;
        }

    private:
        node<T>* _ptr;
    };

    List() : head(nullptr) {}
    ~List() {
        DestroyList(head);
    }

    List(const List<T>& copyThis) {
        head = CopyList(copyThis.Begin());
    }

    List& operator=(const List& RHS) {
        if (this != &RHS) {
            DestroyList(head);
            head = CopyList(RHS.Begin());
        }
        return *this;
    }

    Iterator InsertHead(const T& item) {
        return Iterator(insertHead(head, item));
    }

    Iterator InsertAfter(const T& item, Iterator iMarker) {
        return Iterator(InsertAfter(head, iMarker._ptr, item));
    }

    Iterator InsertBefore(const T& item, Iterator iMarker) {
        return Iterator(InsertBefore(head, iMarker._ptr, item));
    }

    Iterator InsertSorted(const T& item) {
        return Iterator(InsertSorted(head, item, true));
    }

    Iterator Search(const T& key) const {
        return Iterator(Search(head, key));
    }

    Iterator Prev(node<T>* iMarker) const {
        return Iterator(previousNode(head, iMarker));
    }

    node<T>* Begin() const {
        return head;
    }

    Iterator End() const {
        return Iterator(nullptr);
    }

    T Delete(node<T>* iMarker) {
        return DeleteNode(head, iMarker);
    }

    void Print() const {
        PrintList(head);
    }

    T& operator[](int index) {
        node<T>* current = head;
        for (int i = 0; i < index && current != nullptr; ++i) {
            current = current->_next;
        }
        if (!current) throw std::out_of_range("Index out of range");
        return current->_item;
    }

    void PrintCursor(Iterator cursor) const {
        Iterator iter(head);
        while (iter != End()) {
            if (iter == cursor) {
                std::cout << "{" << *iter << "}->";
            }
            else {
                std::cout << "[" << *iter << "]->";
            }
            ++iter;
        }
        std::cout << "|||" << std::endl;
    }

    template <class U>
    friend std::ostream& operator<<(std::ostream& outs, const List<U>& l) {
        outs << "H->";
        typename List<U>::Iterator iter(l.Begin());
        while (iter != l.End()) {
            outs << *iter << " ";
            ++iter;
        }
        outs << "|||" << std::endl;
        return outs;
    }

private:
    node<T>* head;
};

#endif // LIST_H
