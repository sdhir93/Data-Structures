#include<bits/stdc++.h>
using namespace std;

// Templated Circular Buffer Class
// - Overwrites old data
template <class T>
class Queue
{
private:
    int rear, front; // Rear tracks insertion and front tracks deletion
    int capacity;    // Maximum capacity of the circular buffer
    int size;        // Current No. of valid elements in buffer
    T *arr;          // Pointer to the array of elements

public:
    // Constructor used by client to set capacity
    Queue(int inputCapacity)
    {
        front = rear = -1;
        capacity = inputCapacity;
        arr   = new T[capacity];
        size = 0;
    }

    void enQueue(T value);
    bool deQueue(T& itemStore);
    bool isFull();
    bool isEmpty();
    void displayQueue();
    int getSize();
};

template <class T>
bool Queue<T>::isFull()
{
    // Buffer full condition
    return (front == (rear + 1) % capacity);
}

template <class T>
bool Queue<T>::isEmpty()
{
    // Buffer empty condition
    return (front == -1);
}

// Enqueue value into the buffer
template <class T>
void Queue<T>::enQueue(T value)
{
    // Check if buffer is full
    if( isFull() )
    {
        // Advance front index
        front = (front + 1) % capacity;
    }

    // Increment size
    else size++;

    // If first element, set front  = 0
    else if (front == -1) front = 0;

    // Advance rear index, take care of normal condition and the wrap around
    rear = (rear + 1) % capacity;

    // Insert value in rear index
    arr[rear] = value;
}

// Delete element from the buffer
template <class T>
bool Queue<T>::deQueue(T& itemStore)
{
    // If buffer is empty
    if ( isEmpty() )
    {
        cout << "Queue is Empty!\n";
        return false;
    }

    // Decrement size
    else size--;

    // Get the item and store it
    itemStore = arr[front];

    if(front == rear)
    {
        front = -1;
        rear = -1;
    }

    // Advance front index, take care of normal condition and the wrap around
    else front = (front + 1) % capacity;

    return true;
}

// Function to display the elements
// of Circular Queue
template <class T>
void Queue<T>::displayQueue()
{
    // Return if buffer is empty
    if ( isEmpty() ) return;

    cout << "Elements in Circular Queue are: " << endl;
    if (rear >= front)
    {
        for (int i = front; i <= rear; i++)
            cout << arr[i] << endl;
    }

    else
    {
        for (int i = front; i < capacity; i++)
            cout << arr[i] << endl;
        for (int i = 0; i <= rear; i++)
            cout << arr[i] << endl;;
    }
}

template <class T>
int Queue<T>::getSize()
{
    return size;
}


/* Driver of the program */
int main()
{
    Queue<int> q(5);
    int a;
    cout << "Curretn Size = " << q.getSize() << endl;
    // Inserting elements in Circular Queue
    q.enQueue(14);
    q.enQueue(22);
    q.enQueue(13);
    cout << "Curretn Size = " << q.getSize() << endl;
    q.enQueue(-6);
    q.enQueue(-4);
    q.enQueue(-61);
    cout << "Curretn Size = " << q.getSize() << endl;
    // Display elements present in Circular Queue
    q.displayQueue();
    // Deleting elements from Circular Queue
    q.deQueue(a);
    q.deQueue(a);
    cout << "Curretn Size = " << q.getSize() << endl;
    q.displayQueue();
    q.enQueue(9);
    q.enQueue(20);
    q.enQueue(5);
    cout << "Curretn Size = " << q.getSize() << endl;
    q.displayQueue();
    q.enQueue(20);
    cout << "Curretn Size = " << q.getSize() << endl;
    return 0;
}