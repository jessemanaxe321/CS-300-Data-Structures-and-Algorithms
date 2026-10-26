# CS 300 Project One: Run-Time and Memory Analysis

**Author:** Jesse Carles  
**Course:** CS 300 - Data Structures and Algorithms  
**Project:** ABC University Advising Assistance Program

## Project overview

For Project One, I compared three ways to store course records for ABC University: a vector, a hash table, and a binary search tree (BST). The advising program needed to read and check course data, look up courses and prerequisites, and print the full course list in alphanumeric order.

For the comparison, **n** is the number of courses and **b** is the number of hash-table buckets. I assumed each course has a limited number of prerequisites. The estimates below also show where average or balanced-tree performance differs from the worst case.

## 1. Vector

| Operation | Cost per execution | Number of executions | Total cost |
| --- | --- | --- | --- |
| Open file | O(1) | 1 | O(1) |
| Read, split, trim, and validate basic record fields | O(1) | n | O(n) |
| Create a Course and copy fields | O(1) | n | O(n) |
| Add a bounded number of prerequisites | O(1) | n | O(n) |
| Append to vector | O(1) amortized | n | O(n) |
| Close file | O(1) | 1 | O(1) |

**Load time:** O(n), since `push_back` has amortized constant-time cost.  
**Memory:** O(n), with possible reserved capacity beyond the number of stored courses.

A vector is straightforward to use and does not have much extra overhead. It also gives direct access by index. The downside is that finding a course by its number requires checking entries one by one unless a separate index is added. The course list also has to be sorted before printing it in order.

## 2. Hash table

| Operation | Cost per execution | Number of executions | Total cost |
| --- | --- | --- | --- |
| Read, parse, and validate records | O(1) | n | O(n) |
| Create Course object | O(1) | n | O(n) |
| Hash course number | O(1) | n | O(n) |
| Insert into a bucket or chained list | O(n) worst case | n | O(n^2) worst case |
| Close file | O(1) | 1 | O(1) |

**Load time:** O(n) expected with a well-distributed hash function and reasonable load factor; O(n^2) worst case for insertion by traversing long collision chains.  
**Memory:** O(n + b), including course records and hash-table buckets.

The main advantage of a hash table is fast lookup by course number, usually O(1). The problem for this assignment is that it does not keep the courses in order. To print the full list alphanumerically, the records would still need to be collected and sorted.

## 3. Binary search tree (BST)

| Operation | Cost per execution | Number of executions | Total cost |
| --- | --- | --- | --- |
| Read, parse, and validate records | O(1) | n | O(n) |
| Create Course and tree node | O(1) | n | O(n) |
| Insert course in BST | O(n) worst case | n | O(n^2) worst case |
| Close file | O(1) | 1 | O(1) |

**Load time:** O(n log n) for a balanced or reasonably shaped tree; O(n^2) worst case if the tree becomes a chain.  
**Memory:** O(n) for nodes, plus traversal stack space proportional to tree height, O(h).

In a BST, each course is placed according to its course number. An in-order traversal prints the courses in order without needing another sort. Searching can be O(log n) when the tree is balanced, but an unbalanced tree can end up behaving more like a linked list. Each node also takes some extra space for its child pointers.

## 4. Operation comparison

| Structure | Load | Find one course | Print sorted list | Memory |
| --- | --- | --- | --- | --- |
| Vector | O(n) | O(n) | O(n log n) | O(n) |
| Hash table | O(n) expected; O(n^2) worst | O(1) expected; O(n) worst | O(n log n) | O(n + b) |
| Binary search tree | O(n log n) balanced; O(n^2) worst | O(log n) balanced; O(n) worst | O(n) in-order | O(n) |

## 5. Advantages and tradeoffs

| Structure | Advantages | Disadvantages |
| --- | --- | --- |
| Vector | Straightforward implementation, relatively low overhead, direct index access, linear-time loading | Unsorted lookup is O(n); sorted output needs sorting |
| Hash table | O(1) expected lookup; useful for repeated exact course-number queries | Does not maintain ordering; collisions can reduce performance |
| Binary search tree | Naturally ordered course numbers; O(n) in-order output; O(log n) search when balanced | A skewed, unbalanced tree can perform poorly; nodes use extra memory for pointers |

## 6. Recommendation

I chose the **binary search tree** for the advising program. Being able to print every course in order was one of the main requirements, and an in-order traversal handles that directly in O(n) time. With a vector or a hash table, I would have to sort the courses separately. A BST also makes it possible to search for one course without checking every record when the tree is reasonably balanced.

The drawback is that my BST is **not self-balancing**. If the courses are inserted in an unfavorable order, searching could take O(n) time and building the tree could take O(n²). Even with that limitation, the BST fit the course-ordering and lookup features I needed for this project.
