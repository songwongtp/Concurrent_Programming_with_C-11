/* Songwong Tasneeyapant
 * C++ Threading #5: Unique Lock and Lazy Initialization
 */

 #include <iostream>
 #include <thread>
 #include <string>
 #include <mutex>
 using namespace std;

 class LogFile {
     std::mutex _mu;
     ofstream _f;

 public:
     LogFile() {
         _f.open("log.txt");
     } // Need destructor to close file
     void shared_print(string msg, int id) {
         //std::lock_guard<std::mutex> guard(_mu);
         std::unique_lock<mutex> locker(_mu, std::defer_lock);  // - similar to lock_guard but provide more flexibility
                                                                // - Can lock/unlock many number of times
                                                                // - Can construct a locker without locking the mutex
                                                                //   Use std::defer_lock

                                                                // A replica of a mutex (lock_guard/unique_lock)
                                                                // can never be copied, but a unique_lock can be moved
                                                                // transfering the ownership of a mutex
                                                                // from one unique_lock to another unique_lock

                                                                // unique_lock is heavy than lock_guard
                                                                // lower the performance of the program
         // do something else

         locker.lock();
         _f << "From " << id << ": " << value << endl;
         locker.unlock();

         // do something

         locker.lock();

         std::unique_lock<mutex> locker2 = std::move(locker);
     }
 };
