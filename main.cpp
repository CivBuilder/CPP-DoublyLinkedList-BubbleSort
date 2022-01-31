/// @file main.cpp
/// @author Chris Catechis
/// @date 1/30/2022
/// @brief Testing the LL class.

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "Assignment01.hpp"

/// function prototype
void bubblesort(LL<int>& list);

int main() {
  std::ifstream infile;  // file to be read in
  LL<int> int_list;  // list to hold ints
  LL<int>::iterator it;  // iterator to track status of readin
  LL<int>::iterator nil(NULL);  // comparison operator
  int item;  // temp int to hold objects from file being read in.
  std::string filename;  // file name to be inputted by user

  // read in the file
  std::cout << "Enter file with list: ";
  std::cin >> filename;
  infile.open(filename);  // attempt to open file

  // check if file opened
  if (infile.good()) {
    // do operations

    while (infile >> item) {  // file read in/insert
      int_list.tailInsert(item);
    }

    // output original list
    std::cout << "Original List\n";
    for (auto iter = int_list.begin(); iter != nil; iter++) {
      std::cout << *iter << " ";
    }
    std::cout << std::endl << "\n";

    bubblesort(int_list);

    // output sorted list
    std::cout << "Sorted List\n";
    for (auto iter = int_list.begin(); iter != nil; iter++) {
      std::cout << *iter << " ";
    }
    std::cout << std::endl << "\n";

    infile.close();  // close the file
  }
}

/// sorts a doubly linked list of objects using the bubble sort algorithm.
/// @param list doubly linked list passed by reference.
void bubblesort(LL<int>& list) {
  LL<int>::iterator i(list.end());  // iterator used for traversal.
  LL<int>::iterator j = list.begin();  // iterator used for traversal.
  LL<int>::iterator j_next = list.begin();  // iterator used for traversal.
  bool swapped = true;  // control object.

  j_next++;  // alignment.

  while (swapped == true) {
    swapped = false;  // set swapped to check if swaps occur.

    while (j_next != nullptr) {
      if (*j > *j_next) {
        list.swapNodes(j, j_next);
        j_next++;
        if (j != i) {  // prevent segfault.
          j_next++;
        }
        swapped = true;
      }
      else {
        j++;  // iterate both, these nodes are in order.
        j_next++;
      }
    }
    j = list.begin();  // reset iterators
    j_next = list.begin();
    j_next++;
    if (swapped != false && i != list.begin()) {   // prevent segfault.
      i--;  // decrement sorted part of list.
    }
  }
}