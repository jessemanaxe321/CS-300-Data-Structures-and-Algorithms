# CS 300 - Data Structures and Algorithms

**Jesse Carles**  
Southern New Hampshire University

This repository contains two projects from CS 300. Both deal with an advising program for ABC University. The program reads a course file, checks prerequisites, lets a student look up a course, and prints the course list in alphanumeric order.

## Project files

- **[Project One - Run-Time and Memory Analysis](Project_One_Runtime_and_Memory_Analysis.md):** My comparison of a vector, a hash table, and a binary search tree (BST). I looked at how each one stores, searches, and prints course information and how much memory it needs.
- **[Project Two - Advising Assistance Program](ProjectTwo.cpp):** The C++ course planner. I used a BST to store courses by course number. The program can print the whole course list in order or look up one course and show its prerequisites.
- **[Sample course file](examples/sample_courses.csv):** A small set of example courses for trying out the program.

## Reflection

### What was the problem you were solving in the projects for this course?

The main problem was figuring out how to organize the course information for ABC University so an advisor or student could use it. The program needed to load the courses from a file, make sure the prerequisites were valid, show the full course list in order, and pull up information about a specific course. In Project One, I worked through which data structure made the most sense. In Project Two, I put that plan into a C++ program.

### How did you approach the problem? Consider why data structures are important to understand.

I broke the program down into the things it needed to do before worrying about the code. Then I compared vectors, hash tables, and binary search trees to see how they handled storing, searching, and printing data. I went with a BST because an in-order traversal prints the courses by course number without having to sort them separately. A hash table would be good for looking up one course, but it does not keep the courses in order. That comparison helped me understand that a data structure should be chosen for what the program actually needs to do, not just because it works.

### How did you overcome any roadblocks you encountered while going through the activities or project?

I had to slow down and work through some of the pointer and sorting logic in this course. Removing items from linked lists and binary search trees was tricky because the code has to handle different situations depending on where the item is. Quicksort also took extra attention because it was easy to lose track of the indexes while partitioning the data. I went back to the pseudocode, worked on one function at a time, and checked the results. For the advising program, I also included checks for files that cannot be opened, incomplete records, and prerequisites that do not match a course in the file.

### How has your work on this project expanded your approach to designing software and developing programs?

This course made me think more about the choices behind a program instead of only whether the output is correct. I learned that the same problem can be solved in different ways, but the run time and memory use can be very different. The BST made sense for this project because printing an ordered list was one of the main requirements. I also know an ordinary BST can slow down if the nodes end up in a bad order, so there is still a tradeoff. I will keep that in mind when planning future programs.

### How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

I have gotten better about separating the code into functions instead of trying to do everything in one place. In Project Two, loading the file, validating the data, inserting courses, searching, and displaying results are handled separately. That makes the program easier to follow and helps me find a problem without digging through the whole thing. I also paid more attention to meaningful names and checking input. Those are habits I want to keep using as my projects get bigger.

## Build and run Project Two

The program uses standard C++ and does not require extra libraries.

1. Compile `ProjectTwo.cpp` with a C++11 or newer compiler:

   ```bash
   g++ -std=c++11 -Wall -Wextra -pedantic ProjectTwo.cpp -o course_planner
   ```

2. Run the program:

   ```bash
   ./course_planner
   ```

   On Windows, run `course_planner.exe`.

3. Select `1` to load a course file and enter `examples/sample_courses.csv`. Then select `2` to print every course or `3` to look up an individual course. Select `9` to exit.

The program expects one course per line, with the course number and title followed by any prerequisites:

```text
CSCI100,Introduction to Computer Science
CSCI200,Data Structures,CSCI100
CSCI300,Introduction to Algorithms,CSCI200,MATH201
MATH201,Discrete Mathematics
```

Every prerequisite must also appear as a course number in the file. This is simple comma-separated data, so course titles should not contain commas.

**Implementation note:** The BST is not self-balancing. An in-order traversal prints courses in O(n) time, while searching is O(log n) in a balanced tree and can reach O(n) if the tree becomes skewed.
