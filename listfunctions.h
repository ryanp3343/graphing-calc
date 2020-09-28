#ifndef LISTFUNCTIONS_H
#define LISTFUNCTIONS_H


#include <iostream>

using namespace std;

template <typename T>
struct node
{
    T _item;
    node<T> * _next;

    friend ostream& operator<<(ostream& outs, const node<T> & printMe);

    node(T item)
    {
        _next=nullptr;
        _item=item;
    }
};

template <typename T>
ostream& operator<<(ostream& outs, const node<T>& printMe)
{
    node<T>* ptr=printMe;
    for(ptr; ptr!= nullptr; ptr=ptr->_next){
        outs<<ptr->_item;
    }
    outs<<endl;
    return outs;
}

template <typename T>
void PrintList(node<T>* head)
{
    node<T>* walker;
    walker=head;
    //empty list
    if(head==NULL)
    {
        return;
    }
    //print value and iterate
    while(walker!=NULL)
    {
        cout<<"["<<walker->_item<<"]->";
        walker=walker->_next;

    }
    cout<<"|||"<<endl;
}

template <typename T>
node<T>* Search(node<T>*_head_ptr, T key)
{

    node<T>* temp=_head_ptr;
    //head is key and return
    if(temp->_item==key)
    {
        return _head_ptr;
    }
    else {
    //iterate through list to search for key then return
        while(temp!=nullptr)
        {
            if(temp->_item==key)
            {
                return temp;
            }
            temp=temp->_next;
        }
    }
    return nullptr;
}
template <typename T>
node<T>* insertHead(node<T> *&head, T insertThis)
{
    //insert new node at head of list next to head pointer
    node<T>* temp= new node<T>(insertThis);
    temp->_next=head;
    head=temp;
    return head;
}
template <typename T>
node<T>* InsertBefore(node<T>*& head, node<T>* before, T insertThis)
{

    node<T>* temp, *prev, *insertHere;
    //head is null then insert head
    if(!head->_next)
    {
        InsertHead(head,insertThis);
        return head;
    }
    //
    else {
        prev=previousNode(head,before);

        if(!prev)
        {
            insertHere=InsertHead(head,insertThis);
            return insertHere;
        }
    }

    temp=new node<T>(insertThis);
    prev=previousNode(head,before);
    //put the data in and make next of new as next of prev
    temp->_next=prev->_next;
    prev->_next=temp;
    return prev;

}

template <typename T>
node<T>* previousNode(node<T>* head, node<T>* prev)
{
    //empty list
    if(!head->_next || head==prev)
    {
        return nullptr;
    }
    node<T>* headWalker=head;
    node<T>* tailWalker=head;
    //head points to next
    headWalker=headWalker->_next;
    //list has 2 items
    if(tailWalker->_next == prev->_next)
        return head;
    //items != iterate
    else
    {
        while(headWalker->_item != prev->_item)
        {
            headWalker=headWalker->_next;
            tailWalker=tailWalker->_next;
        }

    }
    return tailWalker;
}

template <typename T>
T deleteHead(node<T>*& head)
{
    //delete head and point temp node to head next
    node<T>* temp=nullptr;
    T item=head->_item;
    temp=head->_next;
    delete head;
    head=temp;
    return item;
}

template <typename T>
T deleteNode(node<T>& head, node<T>* deleteThis)
{

    T item=deleteThis->_item;
    if(!head->_next)
    {
        deleteHead(head);
        return item;
    }

    node<T>* prev=previousNode(head,deleteThis);

    if(!prev)
    {
        deleteHead(head);
        return item;
    }
    //set prev next to the item to delete next then delete
    node<T>* toDelete=deleteThis;
    prev->_next=toDelete->_next;
    delete [] toDelete;
    return item;


}

template <typename T>
node<T>* CopyList(node<T>* head)
{
    node<T>* src=head;
    node<T>* dest=nullptr;
    node<T>* walker=nullptr;

    while(src != nullptr)
    {
        T insert=src->_item;
        if(dest==nullptr)
        {
            walker=insertHead(dest,insert);
        }
        else
        {
           InsertAfter(dest,walker,insert);
           walker=walker->_next;
        }
        src=src->_next;
    }
    return dest;
}

template <typename T>
node<T>* InsertAfter(node<T>*& head, node<T>*& after, T insertThis)
{
    //new node of item to insert
    node<T>* temp= new node<T>(insertThis);
    if(!after->_next)
    {
        after->_next=temp;
        return temp;
    }
    //after points to nexts node and return
    else {
        temp->_next=after->_next;
        after->_next=after;
        return temp;
    }
}

template <typename T>
void destroyList(node<T>* head)
{
    //iterate and delete
    if (!head)
    {
        delete head;
        return;
    }
    node<T>* nodeWalker = head;
    while (nodeWalker->_next != nullptr)
    {
        nodeWalker = nodeWalker->_next;
        DeleteNode(head, nodeWalker);
    }
    delete head;
}

template <typename T>
T DeleteNode(node<T>*& head, node<T>* deleteThis)
{
    T item=deleteThis->_item;
    if(!head->_next)
    {
        deleteHead(head);
        return item;
    }
    node<T>* before=previousNode(head,deleteThis);
    if(!before)
    {
        deleteHead(head);
        return item;
    }

    node<T>* discard = deleteThis;
    before->_next = discard->_next;

    delete []discard;
    return item;
}

template <typename T>
node<T>* WhereThisGoes(node<T>* head, T item, bool ascending)
{
    if(ascending && item < head->_item)
    {
        return nullptr;
    }
    if(!ascending && item > head->_item)
    {
        return nullptr;
    }

    node<T>* walker=head->_next;
    node<T>* tailWalker=head;

    //return where to inster the item
    while(walker!=nullptr && tailWalker!=nullptr)
    {
        if(!ascending && tailWalker->_item >= item && walker->_item <=item)
        {
            return tailWalker;
        }

        if(ascending && tailWalker->_item <= item && walker->_item >= item)
        {
            return walker;
        }
        walker=walker->_next;
        tailWalker=tailWalker->_next;
    }
    return tailWalker;
}

template <typename T>
node<T> * InsertSorted(node<T>*& head, T item, bool ascending)
{

    node<T>* here;

    if(!head->_next)
    {
        if(!ascending)
            here=InsertHead(head,item);
        else {
            here=InsertAfter(head,head,item);
        }
        return here;
    }
    //find where to instert and then instert item
    node<T>* after=WhereThisGoes(head,item,ascending);

    if(!after)
    {
        here=InsertHead(head,item);
        return here;
    }
    else {
        here=InsertAfter(head,after,item);
    }

    return here;
}

template <typename T>
node<T>* lastNode(node<T>* head)
{
    node<T>* walker =head;
    while (walker!=nullptr)
    {
        walker=walker->_next;
    }
    return walker;
}



#endif // LISTFUNCTIONS_H
