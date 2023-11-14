#ifndef QUEUE_IMP
#define QUEUE_IMP

#include <iostream>
#include <stdexcept>
#include "Node.h"
#include "Queue.h"

template <typename T>
Queue<T>::Queue()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <typename T>
void Queue<T>::enqueue(T item)
{
    /*
    Creates a Node to push to the queue.
    */
    Node<T>* newItem = new Node<T>(item);

    /*
    If there are items in the queue,
    set the tail to the new item.
    If the queue is empty, initialize both the tail and the head to the new item.
    */
    if (tail != nullptr){
        tail->next = newItem;
    }
    else
    {
        head = newItem;
    }
    tail = newItem;

    /*
    Increments the size of the queue to account for the new item.
    */
    size++;
}

template <typename T>
void Queue<T>::dequeue()
{
    /*
    Throws an error if the queue has no items to dequeue.
    Uses the stdexcept library.
    */
    if (size <= 0)
    {
        throw std::domain_error("The queue is empty.");
    }
    /*
    If there's only one item, delete the head and tail, and set them to null.
    */
    else if (size == 1)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    /*
    If there are more than one items, make the head point to the next item, and then delete the old head.
    */
    else
    {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        temp = nullptr;
    }
    size--;
}

template <typename T>
const T Queue<T>::read()
{
    return head->item;
}

template <typename T>
const int Queue<T>::getSize()
{
    return size;
}

#endif