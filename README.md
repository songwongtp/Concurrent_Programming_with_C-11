# Concurrent_Programming_with_C-11
From: Bo Qian <br/>
https://www.youtube.com/playlist?list=PL5jc9xFGsL8E12so1wlMS0r0hTQoJL74M
1. Introduction
2. Thread Management
3. Data Race and Mutex
4. Deadlock
5. Unique Lock and Lazy Initialization
6. Condition Variable
7. Future, Promise, and async()
8. Using Callable Objects
9. packaged_task
10. Review and Time Constrain

### Concurrent Programming
1. Multiprocessing - can use many computers at the same time <br/>
2. Multithreading  - use shared memory, so cannot use more than one computer <br/>
    - The number of threads you should use is the number of cores your computer have
    - Shouldn't remote threads than the hardware can support (Oversubscription)
        - create lots of contact switching
        - degrade the performance

### Avoiding Data Race
1. Use mutex to synchronize data access
2. Never leak a handle of data to outside
3. Design interface appropriately
