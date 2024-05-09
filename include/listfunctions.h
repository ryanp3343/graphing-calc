#ifndef LISTFUNCTIONS_H
#define LISTFUNCTIONS_H

#include <iostream>

// Generic node structure
template <typename T>
struct node {
    T _item;
    node<T>* _next;

    node(const T& item) : _item(item), _next(nullptr) {}

    friend std::ostream& operator<<(std::ostream& outs, const node<T>& printMe) {
        const node<T>* ptr = &printMe;
        while (ptr != nullptr) {
            outs << ptr->_item << " ";
            ptr = ptr->_next;
        }
        return outs;
    }
};

// Print the linked list starting from head
template <typename T>
void PrintList(const node<T>* head) {
    if (!head) {
        std::cout << "Empty list!" << std::endl;
        return;
    }

    const node<T>* walker = head;
    while (walker != nullptr) {
        std::cout << "[" << walker->_item << "]->";
        walker = walker->_next;
    }
    std::cout << "|||" << std::endl;
}

// Search for a node with a specific key
template <typename T>
node<T>* Search(node<T>* head, const T& key) {
    node<T>* temp = head;
    while (temp != nullptr) {
        if (temp->_item == key) {
            return temp;
        }
        temp = temp->_next;
    }
    return nullptr;
}

// Insert at the head of the linked list
template <typename T>
node<T>* insertHead(node<T>*& head, const T& insertThis) {
    node<T>* temp = new node<T>(insertThis);
    temp->_next = head;
    head = temp;
    return head;
}

// Insert a node after a specified node
template <typename T>
node<T>* InsertAfter(node<T>*& head, node<T>*& after, const T& insertThis) {
    if (!after) return head;

    node<T>* temp = new node<T>(insertThis);
    temp->_next = after->_next;
    after->_next = temp;
    return temp;
}

// Delete the head node of the linked list
template <typename T>
T DeleteHead(node<T>*& head) {
    if (!head) throw std::runtime_error("Attempted to delete head of an empty list");

    node<T>* temp = head;
    T item = temp->_item;
    head = head->_next;
    delete temp;
    return item;
}

// Copy a linked list
template <typename T>
node<T>* CopyList(const node<T>* head) {
    const node<T>* src = head;
    node<T>* dest = nullptr;
    node<T>* walker = nullptr;

    while (src != nullptr) {
        const T& insert = src->_item;
        if (!dest) {
            walker = insertHead(dest, insert);
        }
        else {
            walker = InsertAfter(dest, walker, insert);
        }
        src = src->_next;
    }
    return dest;
}

// Destroy all nodes in a linked list
template <typename T>
void DestroyList(node<T>*& head) {
    while (head) {
        node<T>* temp = head;
        head = head->_next;
        delete temp;
    }
    head = nullptr;
}

// Find where to insert an item in a sorted list
template <typename T>
node<T>* WhereToInsert(node<T>* head, const T& item, bool ascending) {
    node<T>* walker = head;
    node<T>* previous = nullptr;

    while (walker) {
        if ((ascending && walker->_item >= item) || (!ascending && walker->_item <= item)) {
            return previous;
        }
        previous = walker;
        walker = walker->_next;
    }
    return previous;
}

// Insert an item into a sorted list
template <typename T>
node<T>* InsertSorted(node<T>*& head, const T& item, bool ascending) {
    node<T>* before = WhereToInsert(head, item, ascending);
    if (!before) {
        return InsertHead(head, item);
    }
    else {
        return InsertAfter(head, before, item);
    }
}

// Find the last node in a linked list
template <typename T>
node<T>* LastNode(node<T>* head) {
    node<T>* walker = head;
    if (!walker) return nullptr;

    while (walker->_next) {
        walker = walker->_next;
    }
    return walker;
}

template <typename T>
node<T>* previousNode(node<T>* head, node<T>* target) {
    // Check if the list is empty or the target is at the head
    if (!head || head == target) {
        return nullptr;
    }

    // Traverse the list to find the node that precedes the target
    node<T>* current = head;
    while (current && current->_next != target) {
        current = current->_next;
    }

    // If the loop ended without finding the target, return nullptr
    if (!current || current->_next != target) {
        return nullptr;
    }

    return current;
}


template <typename T>
T DeleteNode(node<T>*& head, node<T>* deleteThis) {
    // If the head node is the node to be deleted, use `deleteHead`
    if (head == deleteThis) {
        return DeleteHead(head);
    }

    // Find the previous node
    node<T>* prev = previousNode(head, deleteThis);
    if (!prev || !deleteThis) {
        throw std::runtime_error("Node to be deleted is not found in the list.");
    }

    // Disconnect the node to be deleted from the list
    prev->_next = deleteThis->_next;

    // Retrieve the item and delete the node
    T item = deleteThis->_item;
    delete deleteThis;
    return item;
}


#endif // LISTFUNCTIONS_H
