# merge_insertion_sort

This repository contains the implementation of the Ford-Johnson algorithm, also known as Merge Insertion Sort. This algorithm is a comparison sort that aims to minimize the worst-case number of comparisons for small datasets. Although it might not be the fastest or the most memory efficient, it is particularly useful in scenarios where the cost of comparison significantly outweighs the overhead of the algorithm, such as when each comparison is extremely expensive, for example, making a network request, querying a database, or asking for human input

# instalation & usage

`$ git clone https://github.com/lsemlali-13/merge_insertion_sort`

<img src="https://github.com/lsemlali-13/merge_insertion_sort/assets/74025428/883e3f20-bc5c-4e2d-a684-613bc06b56e0">

# How it Works!!

this is the step by step of how the ford johnson algorithm using works for `n` elements:

1. **Grouping**: Group the elements into `⌊ n / 2 ⌋` pairs of elements, arbitrarily, saving the last element if there is an odd number of elements .

2. **Sorting Pairs**: Perform `⌊ n / 2 ⌋` comparisons, one per pair, to determine the larger of the two elements in each pair.

3. **Recursive Sorting**: Recursively sort the `⌊ n / 2 ⌋` larger elements from each pair, creating a sorted sequence `S` of `⌊ n / 2 ⌋` of the input elements, in ascending order.

4. **Insertion**: Insert at the start of `S` the element that was paired with the first and smallest element of `S`. Insert the remaining `⌈ n / 2 ⌉ − 1` elements into `S`, one at a time, with a specially chosen insertion ordering.

5. **Binary Search**: Use binary search in subsequences of `S` to determine the position at which each element should be inserted. The algorithm is designed to take advantage of the fact that binary searches used to insert elements into are most efficient when the length of the subsequence that is searched is one less than a power of two.

# Example

lets consider this example [3, 8, 2, 7, 5, 1, 9, 0, 1].

### grouping numbers to pairs

in this example we have 9 numbers wich is odd means we save the last element wich is 1 to be inseted last.

<img src="https://www.imghost.net/ib/K5oLAA9vpZx3jBQ_1697146708.png">

### sort each pair

<img src="https://i.postimg.cc/FR139TTf/Screenshot-from-2023-10-12-22-39-51.png">

### sort pairs by larger numbers by recursion using merge insertion

in this step you should keep track of the order of the larger numbers so you can rearrange the smaller ones after.

<img src="https://www.imghost.net/ib/mcXO2Hxy61qgpUK_1697148106.png">

### create main chain and pend chain

the main chain where you put the larger numbers means the first number of each pair, and the pend is where you put the smallest numbers.

<img src="https://www.imghost.net/ib/5yfH5Zoh3FXO57z_1697147875.png" alt="Screenshot from 2023-10-12 22-57-45.png">

## insertion

first insert the first number of pend elements to begining of main chain.

<img src="https://www.imghost.net/ib/TeGHq42rOq1LNHz_1697148212.png">

then we insert the rest of the pend elements by this order 3, 2, 5, 4, 11, 10, 9, 8... this order can be determened by a sequence called the jacob sthal 1, 3, 5, 11, the first element was already inserted, so we start by 3, in this example the sequence would be 3, 2, 4 and each element will be inserted using binary search into the main chain.


