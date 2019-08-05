#include <assert.h>

/*
    This class is for a double linked list object
    and some of its simple behaviours
*/

template <class T>
class List
{
public:
    // Constructor
    List() : head_(nullptr), tail_(nullptr){};

    // Destructor
    ~List();

    // Adds element as new head
    void PushFront(T);

    // Add element as new tail
    void PushBack(T);

    // Removes head and returns its value
    T PopFront();

    // Removes tail and returns its value
    T PopBack();

    // Checks if list is empty
    bool IsEmpty() const
    {
        return head_ == nullptr;
    }

    // Gets number of elements in list
    int GetSize() const;

private:

    // Node struct for its members and constructor
    struct Node
    {
        T value;
        Node* prev;
        Node* next;
        Node(T val, Node* prev, Node* next) : value(val), prev(prev), next(next) {}
    };

    Node* head_; // head of the double linked list
    Node* tail_; // tail of the double linked list
};

// Adds an element as head of the list
template <class T> void List<T>::PushFront(T value)
{
    // Create a new node using Node constructor
    head_ = new Node(value, nullptr, List::head_);

    // Check if this is first element in the list
    if (tail_ == nullptr)
    {
        tail_ = head_;
    }
    else
    {
        head_->next->prev = head_;
    }
}

// Adds an element as tail of the list
template <class T> void List<T>::PushBack(T value)
{
    // Create a new node using Node constructor
    tail_ = new Node(value, List::tail_, nullptr);

    // Check if this is first element in the list
    if (head_ == nullptr)
    {
        head_ = tail_;
    }
    else
    {
        tail_->prev->next = tail_;
    }
}

// Delete head of the list
template <class T> T List<T>::PopFront()
{
    if(List::IsEmpty())
    {
        throw("Cannot List::PopFront() when List::Empty()");
    }

    // Create a temporary node using copy constructor
    Node* temp(head_);
    T value = head_->value;

    //update head
    head_ = head_->next;

    // Check if there is atleast 1 element in the list
    if(List::head_)
    {
        // Previous of new head should be nullptr
        head_->prev = nullptr;
    }
    else
    {
        // There is no element in list now
        tail_ = nullptr;
    }

    delete temp;
    return value;
}

// Delete tail of the list
template <class T> T List<T>::PopBack()
{
    if(List::IsEmpty())
    {
        throw("Cannot List::PopBack() when List::Empty()");
    }

    // Create a temporary node using copy constructor
    Node* temp(tail_);
    T value = tail_->value;

    //update tail
    tail_ = tail_->prev;

    // Check if there is atleast 1 element in the list
    if(List::tail_)
    {
        // Next of new tail should be nullptr
        tail_->next = nullptr;
    }
    else
    {
        // There is no element in list now
        head_ = nullptr;
    }

    delete temp;
    return value;
}

// Get number of element sin the list
template <class T> int List<T>::GetSize() const
{
    int size = 0;

    // Create a node using copy constructor
    Node* ptr(head_);
    while (ptr!=nullptr)
    {
        size++;
        ptr = ptr->next;
    }

    return size;
}

// Destructor for List to destroy all elements
template <class T> List<T>::~List()
{
    while(head_)
    {
        // Create a node using copy constructor
        Node* temp(head_);

        // Update head
        head_ = head_->next;

        // delete node that is no longer on the list
        delete temp;
    }
}

int main() {
  // Sanity test
  List<int> list1;
  list1.PushBack(9);
  assert(list1.GetSize() == 1);

  // Deeper test
  List<int> list2;
  list2.PushFront(9);
  list2.PushBack(10);
  assert(list2.GetSize() == 2);
  assert(list2.PopBack() == 10);
  assert(list2.PopFront() == 9);
  assert(list2.GetSize() == 0);
}