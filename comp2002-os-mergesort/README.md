Assignment 2: Parallel Merge Sort

Project Number/Title
* Project: Assignment 2 – Multi-Threaded Parallel Merge Sort
* Authors: Joe Byjo Puthussery, Subhashree Liri Das
* Group name: group 16

## Overview
This project implements a parallel merge sort algorithm in C using the pthreads library. The program sorts an array of randomly generated integers using a divide and conquer approach, creating multiple threads to process separate portions of the array concurrently. A configurable cutoff level controls the depth of thread creation, with conventional single threaded merge sort used to complete the sorting process once the cutoff is reached.

## Manifest



```
.
├── Makefile                 makefile to make compilation and development easier
├── README.md    	    	 Documents the project, its implementation, usage and testing process           
├── mergesort.c              Implements serial merge sort, the merge operation, parallel merge sort and argument construction
├── mergesort.h              header file
└── test-mergesort.c         Generates random arrays, executes the sorting functions, verifies sorting correctness and measures execution time
```

## Building the Project

1. Requirements:
```
GCC compiler
GNU Make
POSIX threads (pthread)
```

2. To compile the program, navigate to the project directory and execute:
```
make clean
make
```

This compiles the source files and generates the test-mergesort executable.

3. To run the program:
```
./test-mergesort <input_size> <cutoff_level> <seed>
Example:

./test-mergesort 1000000 4 1234
```
The arguments are:
1. Input size: Specifies the number of integers to generate and sort.
2. Cutoff level: Determines the maximum depth at which additional threads are created. A cutoff of 0 executes the sorting process using a single thread.
3. Seed: Specifies the random seed used to generate the input array.


## Features and Usage

The program implements the following functionality:
* Single threaded merge sort: Uses recursive merge sort to sort the entire array using a single thread
* Parallel merge sort: Divides the array into smaller subarrays and uses pthreads to process them concurrently
* Configurable thread creation: Uses a cutoff level to control the depth at which additional threads are created
* Thread synchronisation: Uses pthread_join() to ensure child threads complete their sorting operations before their parent merges the results
* Temporary storage: Uses an auxiliary array to temporarily store elements during merging
* Performance measurement: Measures and compares the execution time of the single-threaded and parallel implementations



## Testing
Testing focuses on verifying sorting correctness and evaluating the performance improvement achieved through multithreading.

1. Sorting Correctness
The testing program generates an array of random integers and executes the single-threaded merge sort implementation. It then checks whether the resulting array is sorted using the check_if_sorted() function.
The same random input is subsequently regenerated using the original seed before executing the parallel merge sort implementation. This ensures that both implementations are tested against identical input data.

2. Different Cutoff Levels and Performance Testing
Initial performance tests were conducted using an input size of 100,000,000 elements and a random seed of 1234. Three test runs were recorded to compare the execution times of the single-threaded and parallel implementations.
The results are shown below:

| Test | Input Size  | Cutoff Level | Serial Time (s) | Parallel Time (s) | Speedup |
| ---- | ----------- | ------------ | --------------- | ----------------- | ------- |
| 1    | 100,000,000 | 0            | 29.56           | 28.69             | 1.03×   |
| 2    | 100,000,000 | 1            | 27.20           | 15.15             | 1.79×   |
| 3    | 100,000,000 | 2            | 27.03           | 9.41              | 2.87×   |
| 4    | 100,000,000 | 3            | 27.40           | 6.22              | 4.41×   |
| 5    | 100,000,000 | 4            | 27.39           | 6.21              | 4.41×   |

Speedup was calculated using the formula:
`Speedup = Serial Execution Time / Parallel Execution Time`

The initial results indicate that the parallel implementation can improve sorting performance. However, execution times for smaller input sizes are relatively short, meaning that thread creation overhead and timing precision can influence the measurements.

## Known Bugs

1. creating too many threads introduce additional overhead and that can reduce performance
2. performance varies according to system's CPU and hardware

## Reflection and Self Assessment

During the development of this project, one of the main challenges was understanding how to extend the conventional recursive merge sort algorithm into a parallel implementation using POSIX Threads (pthreads). Although the serial implementation follows a relatively straightforward divide and  conquer approach, introducing concurrency required additional consideration of thread creation, argument passing, synchronisation and memory management.

An important part of the implementation was understanding how pthread_create() and pthread_join() work together. Initially, the relationship between recursive function calls and independently executing threads required careful consideration. This was addressed by using the struct argument structure to pass the left and right array boundaries, together with the current recursion level, to each newly created thread. The buildArgs() function was implemented to allocate and initialise these arguments. This helped establish a consistent way of passing the necessary information to the parallel sorting function.

Memory management was another important consideration. Since each thread receives a dynamically allocated argument structure, these structures must remain valid while the corresponding threads are executing. The implementation addresses this by freeing the child argument structures after the parent has joined both threads. This provided a practical understanding of memory ownership and the importance of managing dynamically allocated resources in multithreaded programs.

Performance testing provided a further opportunity to evaluate the implementation. Initial tests using 100,000 elements showed varying speedup results across different cutoff levels. More importantly, the large-scale test using 100,000,000 elements recorded a single-threaded execution time of 37.03 seconds and a parallel execution time of 10.81 seconds. This produced an approximate speedup of 3.43 times, exceeding the assignment's required target of 2 times.

Overall, this project strengthened our understanding of recursive algorithms, parallel execution, thread synchronisation and shared-memory programming. One of the most important concepts we developed was recognising that successful parallelisation involves more than dividing a problem into smaller tasks. It also requires coordinating their execution, managing shared resources and ensuring that the final results remain correct. The development and testing process helped connect these theoretical concepts with their practical application in C programming.


Sources Used
1. Assignment 2 specifications
2. Operating Systems: Three Easy Pieces. Chapter 27 - Intro to Threads
3. Operating Systems: Three Easy Pieces. Chapter 27 – Threads API
4. OpenAI ChatGPT. Used for explanations of recursive merge sort, pthread functionality, thread synchronisation and memory management 