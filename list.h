#ifndef LIST_H
#define LIST_H
#include <iostream>
#include "listfunctions.h"

using namespace std;


template <typename T>
class List
{
public:
    class Iterator {

        Iterator()
        {
            _ptr = NULL;
        }
        Iterator(node<T>* tmp)
        {
            _ptr = tmp;
        }

        Iterator next()
        {
            return Iterator(_ptr + 1);
        }
        T& operator *()
        {
            return _ptr->_item;
        }

        T* operator ->() {

            Iterator hold;
            hold._ptr = this;
            return hold._ptr;
        }
        const node<T>* operator ->()const {

            return _ptr;
        }

        friend Iterator operator ++(Iterator& it, int unused)
        {
            Iterator hold;
            hold = it;
            it._ptr++;
            return hold;
        }

        Iterator& operator ++()
        {
            _ptr++;
            return *this;
        }

        bool is_null()
        {
            return(!_ptr);
        }
        friend bool operator !=(const Iterator& left, const Iterator& right)
        {
            return left._ptr != right._ptr;
        }

        friend bool operator ==(const Iterator& left, const Iterator& right)
        {
            return(left._ptr == right._ptr);
        }

    private:
        node<T>* _ptr;

    };

    List();
    ~List();
    List& operator=(const List& RHS);
    List(const List<T>& copyThis);


    node<T>* InsertHead(T i);
    Iterator InsertAfter(T i, Iterator iMarker);
    Iterator InsertBefore(T i, Iterator iMarker);
    Iterator InsertSorted(T i);
    Iterator Search(const T& key);
    Iterator Prev(node<T>* iMarker);
    node<T>* Begin() const;
    Iterator End() const;
    T        Delete(node<T>* iMarker);
    void     Print() const;

    T& operator[](int index);
    void    PrintCursor(Iterator cursor) const;

    // friends
    template <class U>
    friend ostream& operator <<(ostream& outs, const List<U>& l);   // insertion operator for list

private:
    node<T>* head;
};

template <class T>
List<T>::List()
{
    head = NULL;
}

template <class T>
List<T>::~List()
{
    //list function to destroy
    destroyList(head);

}

template <class T>
List<T>& List<T>::operator=(const List& RHS)
{
    //copylist over
    if (this != &RHS)
    {
        destroyList(head);
        head = CopyList(RHS.Begin());
    }
    return *this;
}

template <class T>
List<T>::List(const List<T>& listToCopy)
{
    //copy list over
    head = CopyList(listToCopy.Begin());

}

template <class T>
node<T>* List<T>::InsertHead(T i)
{
    //list function to instert head
    node<T>* temp = insertHead(head, i);
    return temp;
    //    if (head == nullptr)
    //    {
    //        head = new node<T>(i);

    //    }
    //    else
    //    {
    //        node<T>* tmp = new node<T>(i);
    //        tmp->_next = head;
    //        head = tmp;
    //    }
    //    return Iterator(head);
}

template <class T>
typename List<T>::Iterator List<T>::InsertAfter(T i, Iterator iMarker)
{

    //list function to instert after
    node<T>* temp = InsertAfter(head, iMarker, i);
    return Iterator(temp);
    //    Iterator iter_tmp(head);
    //    while (iter_tmp != nullptr)
    //    {

    //        if (!(iter_tmp != iMarker))
    //        {
    //            node<T>* tmp = new node<T>(i);
    //            tmp->_next = iter_tmp->_next;
    //            iter_tmp->_next = tmp;
    //            return Iterator(tmp);

    //        }
    //        iter_tmp = iter_tmp->_next;
    //    }
    //    return nullptr;
}


template <class T>
typename List<T>::Iterator List<T>::InsertBefore(T i, Iterator iMarker)
{

    //list function to instert before
    node<T>* temp = InsertBefore(head, iMarker, i);
    return Iterator(temp);

}

template <class T>
typename List<T>::Iterator List<T>::InsertSorted(T i)
{

    //    node<T>* iter_tmp = head;
    //    while (iter_tmp != nullptr)
    //    {
    //        if (i <= iter_tmp->_item)
    //        {
    //            node<T>* tmp = new node<T>(i);
    //            tmp->_next = iter_tmp;
    //            iter_tmp = tmp;
    //            return Iterator(iter_tmp);

    //        }
    //        else if (iter_tmp->_next == nullptr)
    //        {
    //            iter_tmp->_next = new node<T>(i);
    //            return Iterator(iter_tmp->_next);

    //        }
    //        else
    //        {
    //            iter_tmp = iter_tmp->_next;
    //        }
    //    }
    //    return nullptr;

        //list function to instert before
    node<T>* here = InsertSorted(head, i);
    return Iterator(here);
}
template <class T>
typename List<T>::Iterator List<T>::Search(const T& key)
{
    //    Iterator iter_tmp = head;
    //    while (iter_tmp != nullptr)
    //    {
    //        if (iter_tmp->_item == key)
    //        {
    //            cursor=iter_tmp;
    //            break;

    //        }
    //        else
    //        {
    //            iter_tmp = iter_tmp->_next;
    //        }
    //    }
    //    return cursor;

        //list function to search
    node<T>* found = Search(head, key);
    return Iterator(found);
}



template <class T>
typename List<T>::Iterator List<T>::Prev(node<T>* iMarker)
{

    //list function to return previous node
    node<T>* prev = previousNode(head, iMarker);
    return Iterator(prev);

}


template <class T>
node<T>* List<T>::Begin() const
{
    //returns the head of list
    if (!head)
        return nullptr;

    else
        return head;
}

template <class T>
typename List<T>::Iterator List<T>::End() const
{

    //    Iterator iter(head);
    //    while (true)
    //    {
    //        if (iter->_next == NULL)
    //        {
    //            return iter;
    //        }
    //        else {
    //            iter=iter->_next;
    //        }
    //    }

        //returns last node of list
    node<T>* end;
    end = lastNode(head);
    return Iterator(end);
}

template <typename U>
istream& operator >>(istream& ins, node<U>& n)
{
    //to insert

    ins >> n._item;
    return ins;
}


template <class U>
ostream& operator << (ostream& out, const List<U>& l)
{

    //to print
    typename List<U>::Iterator iter(l.Begin());
    cout << "H->";
    while (true)
    {

        out << *iter;
        if (iter != l.End())
        {

            iter = iter->_next;
        }
        else {

            break;
        }


    }
    cout << "|||" << endl;
    return out;
}

template <class T>
T List<T>::Delete(node<T>* iMarker) {


    //list function to delete node
    T item = DeleteNode(head, iMarker);
    return item;

}

template <class T>
void List<T>::PrintCursor(Iterator cursor) const {

    //prints cursor
    Iterator iter = Begin();
    while (true) {

        if (!(iter != cursor))
        {
            cout << "{" << iter->_item << "}->";
        }
        else
        {
            cout << "[" << iter->_item << "]->";
        }
        if (!(iter != End()))
        {
            break;
        }

        iter = iter->_next;
    }
    cout << endl;
}







#endif // LIST_H