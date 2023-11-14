#ifndef LINKED_LIST_IMP
#define LINKED_LIST_IMP

#include "Node.h"
#include "LinkedList.h"

template <typename T>
LinkedList<T>::LinkedList()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <typename T>
Node<T>* LinkedList<T>::getHead()
{
    return head;
}

template <typename T>
Node<T>* LinkedList<T>::getTail()
{
    return tail;
}

template <typename T>
const int LinkedList<T>::getSize()
{
    return size;
}

template <typename T>
void LinkedList<T>::append(T item)
{
    /*
    Creates a new node.
        Sets its item to the give item.
        Sets its next node to a null pointer.
    */
    Node<T>* newItem = new Node<T>(item);

    /*
    Updates the tail value.
        The end of the list will point to this new node.
        This new node becomes the end of the list.
        If the list is empty, initialize both the tail and the head to the new item.
    */
    if (tail != nullptr)
    {
        tail->next = newItem;
    }
    else
    {
        head = newItem;
    }
    tail = newItem;

    /*
    Increments the size of the list.
    */
    size++;
}

#endif