# merge_insertion_sort

This repository contains the implementation of the Ford-Johnson algorithm, also known as Merge Insertion Sort. This algorithm is a comparison sort that aims to minimize the worst-case number of comparisons for small datasets. Although it might not be the fastest or the most memory efficient, it is particularly useful in scenarios where the cost of comparison significantly outweighs the overhead of the algorithm, such as when each comparison is extremely expensive, for example, making a network request, querying a database, or asking for human input

# instalation & usage

`git clone https://github.com/lsemlali-13/merge_insertion_sort`

<img src="https://github.com/lsemlali-13/merge_insertion_sort/assets/74025428/883e3f20-bc5c-4e2d-a684-613bc06b56e0">

# How it Works!!

this is the step by step of how the ford johnson algorithm using works for `n` elements:

1. **Grouping**: Group the elements into `⌊ n / 2 ⌋` pairs of elements, arbitrarily, saving the last element if there is an odd number of elements .

2. **Sorting Pairs**: Perform `⌊ n / 2 ⌋` comparisons, one per pair, to determine the larger of the two elements in each pair.

3. **Recursive Sorting**: Recursively sort the `⌊ n / 2 ⌋` larger elements from each pair, creating a sorted sequence `S` of `⌊ n / 2 ⌋` of the input elements, in ascending order.

4. **Insertion**: Insert at the start of `S` the element that was paired with the first and smallest element of `S`. Insert the remaining `⌈ n / 2 ⌉ − 1` elements into `S`, one at a time, with a specially chosen insertion ordering.

5. **Binary Search**: Use binary search in subsequences of `S` to determine the position at which each element should be inserted. The algorithm is designed to take advantage of the fact that binary searches used to insert elements into are most efficient when the length of the subsequence that is searched is one less than a power of two.

# Detailed Explanation using Example

lets consider this example [3, 8, 2, 7, 5, 1, 9, 0, 1].

1st step would give us: 

<img src="https://www.imghost.net/WEc7KwdFKKeF5P2">
