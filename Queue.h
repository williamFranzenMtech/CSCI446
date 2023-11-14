#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"

template <typename T>
class Queue
{
    private:
        Node<T>* head;
        Node<T>* tail;
        int size;

    public:
        /*
        Constructor
        Description:
            Initializes a queue.
        */
        Queue();

        /*
        Enqueue
        Description:
            Adds an item to the queue.
            Places it after the tail node.
        Params:
            item - An item to add to the queue.
        */
        void enqueue(T item);

        /*
        Dequeue
        Description:
            Removes an item from the queue.
            Deletes the head node.
        */
        void dequeue();

        /*
        Read
        Description:
            Reads the head node.
        Returns:
            The item at the head node.
        */
        const T read();

        /*
        Get Size
        Description:
            Gets the quantity of items in the queue.
        Returns:
            An integer containing the number of items in the queue.
        */
        const int getSize();
};



#endif