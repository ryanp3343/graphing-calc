#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "listfunctions.h"


using namespace std;



template <class T>
class Queue
{
public:

    class Iterator
    {
    public:

            Iterator(node<T>* p = NULL) :_ptr(p) {}

            Iterator next()
            {
                return Iterator(_ptr+1);
            }

            T& operator *()
            {
                return _ptr->_item;
            }

            T* operator ->() {

                Iterator hold;
                hold._ptr=this;
                return hold._ptr;
            }

            const node<T>* operator ->()const {

                return _ptr;
            }

            friend Iterator operator ++(Iterator& it,int unused)
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

            Iterator& operator =(node<T>* tmp) {

                _ptr = tmp;
                return *this;
            }

            bool is_null()
            {
                return(!_ptr);
            }

            friend bool operator !=(const Iterator& left,const Iterator& right)
            {
                return left._ptr != right._ptr;
            }

            friend bool operator ==(const Iterator& left, const Iterator& right)
            {
                return(left._ptr==right._ptr);
            }

                private:
                    node<T>* _ptr;
    };

    Queue();
    ~Queue();
    Queue(const Queue<T> &copyThis);
    Queue& operator =(const Queue& RHS);
    void push(const T& item);
    T pop();
    bool empty() const;
    Iterator Begin() const;
    Iterator End() const;
    void Print(Queue<T>& printMe);


    //to print queue
    friend ostream& operator <<(ostream& outs, const Queue<T>& l){

        for(node<T>* ptr= l._head_ptr; ptr!=nullptr; ptr->_next)
        {
            outs<<"["<<ptr->_item<<"]->";
         }
            outs<<"|||"<<endl;
            return outs;
    }


private:
    node<T> * _head_ptr;
    node<T> * _tail;


};


template <class T>
typename Queue<T>::Iterator Queue<T>::Begin() const
{

    //returns iterator of the beginning of the queue
    return Iterator(_head_ptr);
}

template <class T>
typename Queue<T>:: Iterator Queue<T>::End() const
{
    //returns iterator to end of queue
    if(_tail!=NULL)
        return Iterator(_tail);
}

template <class T>
Queue<T>::Queue()
{

     //default head and tail are null
    _head_ptr=NULL;
    _tail=NULL;

}

template <class T>
Queue<T>::~Queue()
{
    //delelte the list
    destroyList(_head_ptr);
    _tail=nullptr;

}

template <class T>
Queue<T>::Queue(const Queue<T> &copyThis)
{
    //list function to copy list
    _head_ptr=_tail=NULL;
    _head_ptr=CopyList(copyThis._head_ptr);
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue& RHS)
{
    //list fucntion to copy list
    if(this != &RHS)
    {
        if(_head_ptr)
            destroyList(_head_ptr);
        _head_ptr=CopyList(RHS._head_ptr);
    }
}

template <class T>
void Queue<T>::push(const T &item)
{
    //head is null insert new head
    if(!_head_ptr)
    {
        _head_ptr=insertHead(_head_ptr,item);
        _tail=_head_ptr;
    }
    //else instert after
    else
    {
        _tail=InsertAfter(_head_ptr,_tail,item);
    }
}

template <class T>
T Queue<T>::pop()
{
    //delete head of queue
    T result=deleteHead(_head_ptr);

    return result;
}

template <class T>
bool Queue<T>::empty() const
{
    //returns true if queue is empty
    return (_head_ptr==NULL);

}

template <class T>
void Queue<T>::Print(Queue& printMe)
{
    //to print list
    PrintList(printMe._head_ptr);
}


#endif // QUEUE_H
