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
     std::mutex _mu_open;
     std::once_flag _flag;
     ofstream _f;

 public:
     LogFile() {
     } // Need destructor to close file
     void shared_print(string msg, int id) {
         // open the file when only necessay (Lazy Initialization)
         // {
         //    // waste time on useless locking everytime
         //    std::unique_lock<mutex> locker2(_mu_open);
         //    if(!_f.is_open()){
         //         _f.open("log.txt");
         //     }
         // }

         // Instead of using another mutex
         // standard library already provides a solution specifically for this kind of problem
         std::call_once(_flag, [&](){ _f.open("log.txt"); }); // file will be opened only once by one thread

         std::unique_lock<mutex> locker(_mu, std::defer_lock);
         _f << "From " << id << ": " << value << endl;
     }
 };
