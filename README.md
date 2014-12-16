Malloc
======
Arnesh Sahay & Krishna Yellayi                                                                             Systems Programming
Assignment 6: Error-detecting malloc() and free()                                                      December 14, 2014

Design
Data Structures: This assignment required us to create enhanced malloc() and free() functions. The improved malloc() and free() functions are more robust to detect errors that may arise from certain situations that may result in misallocated memory. The memory block data structure used for the functions is a doubly linked list of size 5000.

Functionality: A MemEntry is the block of data that is used by malloc() or free(). Each MemEntry is one of 5000 nodes in a doubly linked list that corresponds to the memory that can allocated to be used by the malloc() and free() functions. Malloc() dedicates a portion of doubly linked list memory to store data. Free() empties a portion of doubly linked list memory. Test cases were developed to ensure that the malloc() and free() functions can handle errors. Calloc() allocates a number of memory blocks and sets the values of those blocks to zero. FragRed() is a fragmentation reduction function to ensure that efficiency is maintained by properly defragmenting the memory to avoid gaps in between data.

Memory: The memory usage is set to be 1048576 Bytes (or 1Mb).

Complexity Analysis
The worst case time complexity to malloc() a MemEntry node in the doubly linked list is O(1), and the worst case time complexity to free() a MemEntry in the doubly linked list is also O(1). The time complexity to calloc() a MemEntry is also O(1), but the time complexity to fragRed() the memory blocks is O(n) with n memory blocks being defragmented.
