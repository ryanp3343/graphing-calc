#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <cstddef>
#include "list.h"

using namespace std;

template <class T>
class Stack
{
public:

    class Iterator{

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


    Stack();
    ~Stack(){}
    void push (T item);
    T pop ();
    T top();
    void Print(Stack&);
    bool empty() const;
    Iterator begin() const;
    Iterator End() const;

    template <class U>
    friend ostream& operator <<(ostream& outs, const Stack<U>& l);

    private:

    List<T> stack;
};

template <class T>
Stack<T>::Stack()
{

}

template <class T>
void Stack<T>::push(T item)
{

    //list function to add item to list
    stack.InsertHead(item);
}

template <class T>
T Stack<T>::pop()
{

    //node to start of stack then list function to delete that noode
    T result;
    node<T>* discard=stack.Begin();
    result=stack.Delete(discard);
    return result;
}

template <class T>
T Stack<T>::top()
{
        //return the top of the stack
        node<T>* top=stack.Begin();
        return top->_item;
}

template <class T>
void Stack<T>::Print(Stack& print)
{
    //prints list
    PrintList(print.stack.Begin());
}

template <class T>
typename Stack<T>::Iterator Stack<T>::begin() const
{
    //returns the top of the stack

        return Stack<T>::Iterator(this->stack.Begin());
}

template <class T>
typename Stack<T>:: Iterator Stack<T>::End() const
{
    //list function to end of list and return
    node<T>* ptr=stack.End();
    typename List<T>::Iterator it(ptr);
    return Iterator(it);

}

template <class T>
bool Stack<T>::empty() const {

    //if stack is empty return true
    return (stack.Begin()==NULL);

}


template <class U>
ostream& operator<< (ostream& out, const Stack<U>& l)
{

    //to print stack
    typename Stack<U>::Iterator iter(l.Begin());
    cout << "H->";
    while (true)
    {

        out << *iter;
        if (iter != l.End())
        {

            iter = iter->next;
        }
        else {

            break;
        }


    }
    cout << "|||" << endl;
    return out;
}



#endif // STACK_H
