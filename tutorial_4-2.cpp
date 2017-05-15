/* Songwong Tasneeyapant
 * C++ Threading #4: Deadlock
*/

#include <iostream>
#include <thread>
#include <string>
#include <mutex>
using namespace std;

class LogFile {
    std::mutex _mu;
    std::mutex _mu2;
    ofstream _f;

public:
    LogFile() {
        _f.open("log.txt");
    } // Need destructor to close file

    // using C++ standard library to avoid deadlock
    void shared_print(string msg, int id) {
        // _mu is already locked, use adopt_lock to adopt the owner of the mutex
        // so whenever you go out of the scope, it can unlock the mutex
        std::locl(_mu, _mu2);
        std::lock_guard<std::mutex> locker(_mu, std::adopt_lock);
        std::lock_guard<std::mutex> locker(_mu2, std::adopt_lock)
        _f << "From " << id << ": " << value << endl;
    }
    void shared_print(string msg, int id) {
        std::locl(_mu, _mu2);
        std::lock_guard<std::mutex> locker(_mu, std::adopt_lock);
        std::lock_guard<std::mutex> locker(_mu2, std::adopt_lock)
        cout << "From " << id << ": " << value << endl;
    }
};

void function_1(LogFile& log) {
    for(int i = 0; i > -100; i--){
        log.shared_print(string("From t1: "), i);
    }
}

int main() {
    LogFile log;
    std::thread t1(function_1, std::ref(log));

    for(int i = 0; i < 100; i++){
        log.shared_print2(string("From main: "), i);
    }

    t1.join();

    return 0;
}
