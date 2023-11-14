#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Node.h"

template <typename T>
class LinkedList
{
    private:
        Node<T>* head;
        Node<T>* tail;
        int size;
    
    public:
        /*
        Constructor
        Description:
            Initializes the linked list.
        */
        LinkedList();

        /*
        Get Head
        Description:
            Returns the head node.
        */
        Node<T>* getHead();

        /*
        Get Tail
        Description:
            Returns the tail node.
        */
        Node<T>* getTail();

        /*
        Get Size
        Description:
            Returns the amount of items in the list.
        */
        const int getSize();

        /*
        Append
        Params:
            T item - The item to be added to the list.
        Description:
            Creates a new node with the given item, and sets it as the new tail of the linked list.
        */
        void append(T item);
};
#endif