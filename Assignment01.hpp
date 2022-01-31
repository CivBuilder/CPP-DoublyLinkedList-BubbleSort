/// @file Assignment01.hpp
/// @author Chris Catechis <8000945777>
/// @section 1004
/// @date 1/30/2022
/// @brief This program creates/implements the LL class, a set of nodes
/// in the form of a doubly linked list. 

#ifndef LL_HPP_
#define LL_HPP_

#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>

template <typename type>
class LL {
    struct node {
        type data ;
        node* prev ;
        node* next ;
    };
public:
    class iterator {
    public:
        friend class LL;  // allows us to use private members.

        /// Default Constructor.
        iterator() { current = nullptr; }

        /// Constructor that assigns ptr to current.
        /// @param ptr an iterator pointer.
        iterator(node *ptr) { current = ptr; }

        /// Overload of dereference operator.
        type operator*() const { return current->data; }

        /// Move the iterator over one node to the right.
        const iterator& operator++(int) {
            current = current->next;
            return *this;
        }

        /// Move the iterator over one node to the left.
        const iterator& operator--(int) {
            current = current->prev;
            return *this;
        }

        /// Check if this iterator and rhs iterator point to the same node
        /// @param rhs node to be compared to this.
        /// @return true if this == rhs node, false if otherwise.
        bool operator==(const iterator& rhs) const { return (current == rhs.current); }

        /// Check if this iterator and rhs iterator do not point to the same node
        /// @param rhs node to be compared to this.
        /// @param true if this != rhs node, false if otherwise.
        bool operator!=(const iterator& rhs) const { return !(current == rhs.current); }

    private:
        node* current;
    };

    /// Default Constructor.
    LL();

    /// Deep copy constructor, performs a deep copy of the copy linked linked list.
    /// @param copy linked list to make a deep copy of into 'this'.
    LL(const LL <type>& copy) { *this = copy; }

    /// Deep copy assignment operator.
    /// @param rhs copy rhs into the 'this' object.
    const LL<type>& operator=(const LL<type>& rhs);

    /// Destructor, deallocates the entire linked list. 
    ~LL();

    /// Performs a tail insert.
    /// @param item will be contained in the data field of the new tail node. 
    void tailInsert(const type& item);

    /// Returns an iterator whose current is set to the head pointer
    iterator begin() const { return iterator(head); }

    /// Returns an iterator whose current is set to the tail pointer.
    iterator end() const { return iterator(tail); }

    /// Swaps the location of the nodes referenced by it1 and it2.
    /// @param it1 first node to be swapped.
    /// @param it2 second node to be swapped. 
    void swapNodes(iterator& it1, iterator& it2);

private:
    node* head;
    node* tail;
};

//------------------------------------------------------------------
//------------------------------------------------------------------

// LL CLASS IMPLEMENTATION 

/// Constructor, sets head and tail to nullptr. 
// template <typename type>
template <typename type>
LL<type>::LL() {
    head = tail = nullptr;
}

//------------------------------------------------------------------

/// Deep copy assignment operator.
/// @param rhs copy rhs into the 'this' object.
template <typename type>
const LL<type>& LL<type>::operator=(const LL<type>& rhs) {
    if (this != &rhs) {  // if they are not equal, deallocate memory.
        while (head != nullptr) {  // clear this
            node* temp = head;
            head = head->next;

            delete temp;
        }

        iterator curr = rhs.begin();

        for (curr = curr++; curr != nullptr; curr++) {
            tailInsert(curr);  // tail insert the current item
        }
    }

    return *this;
}

//------------------------------------------------------------------

/// Destructor, deallocates the entire linked list.
template <typename type>
LL<type>::~LL() {
    while (head != nullptr) {  // clear this, one by one
        node* temp = head;  // node to delete
        head = head->next;

        delete temp;
    }
}

//------------------------------------------------------------------

/// Performs a tail insert.
/// @param item will be contained in the data field of the new tail node. 
template <typename type>
void LL<type>::tailInsert(const type& item) {
    node* newNode;  // new node to insert
    newNode = new node;
    newNode->prev = nullptr;
    newNode->next = nullptr;
    newNode->data = item;

    // if empty list
    if (head == nullptr) {
        head = tail = newNode;  // assign head and tail to new node
    }

    else {  // if non-empty list, insert newNode set current tail next to newNode
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
}

//------------------------------------------------------------------

/// Swaps the location of the nodes referenced by it1 and it2.
/// @param it1 first node to be swapped.
/// @param it2 second node to be swapped.
template <typename type>
void LL<type>::swapNodes(iterator& it1, iterator& it2) {
    node* i1 = it1.current;  // i1 set to it1 for reassignment.
    node* i2 = it2.current;  // i2 set to it2 for reassignment.
    
    if (head != tail) {
        if (i1->prev == nullptr && i2->next == nullptr) {  // if only two nodes in the list.
            i1->prev = i2;  // swap traits
            i1->next = nullptr;
            i2->next = i1;
            i2->prev = nullptr;
            head = i2;  // reassign titles
            tail = i1;
        }
        else {
            if (i1->prev != nullptr) {  // if i1 != head
                iterator it1_left = it1;  // creater iterator left of node for reassignment.
                it1_left--;
                i2->prev = it1_left.current;  // swap traits
                it1_left.current->next = i2;
            }
            else {  // if i1 == head, reassign head.
                head = i2;  // reassign head
                i2->prev = nullptr;  // prev == nullptr
            }
            
            if (i2->next != nullptr) {  // if i2 != tail
                iterator it2_right = it2;    // creater iterator right of node for reassignment.
                it2_right++;
                i1->next = it2_right.current;  // swap traits
                it2_right.current->prev = i1;
            }
            else {  // if i2 == tail, reassign tail.
                tail = i1;  // reassign tail
                i1->next = nullptr;  // next == nullptr
            }

            i2->next = i1;  // reassign i2 and i1.
            i1->prev = i2;
        }
    }
}


#endif /* LL_HPP_ */

/* EOF */