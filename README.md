# Concurrent_Programming_with_C-11
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
1. Multiprocessing - can use many computers at the same time
2. Multithreading  - use shared memory, so cannot use more than one computer
    - The number of threads you should use is the number of cores your computer have
    - Shouldn't remote threads than the hardware can support (Oversubscription)
        - create lots of contact switching
        - degrade the performance

### Avoiding Data Race
1. Use mutex to synchronize data access
2. Never leak a handle of data to outside
3. Design interface appropriately

### Avoiding Deadlock
1. Prefer locking single mutex at a time
2. Avoid locking a mutex and then calling user provided function
    - You don't know what the function will do. It might lock another mutex
    - Then you will end up having two mutexes being locked
    - Or it might try to lock the same mutex again
3. If necessary, use std::lock() to lock more than one mutex
    - std::lock() provides some deadlock avoidance algorithm to lock the mutex
4. If using std::lock() is not possible, lock the mutex in same order for all
    - Or provide a hierarchy of mutexes so that when a thread is holding a lower
    level mutex, it is not allowed to lock a higher level

### Locking Granularity (Locking of a resource should happen at an appropriate granularity)
- Fine-grained lock:    protects small amount of
    - locking 2 of this will increase a chance of deadlock
- Coarse-grained lock:  protects big amount of data
    - locking 2 of this will decrease the opportunity of parallel computing



#### by Bo Qian (http://boqian.weebly.com)
