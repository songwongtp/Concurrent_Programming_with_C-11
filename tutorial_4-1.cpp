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

    // Deadlock situation: t1 locks _mu, while main locks _mu2
    // To avoid Deadlock, put locking mutexes in the same order

    // or using C++ standard library, shown in tutorial_4-2.cpp
    void shared_print(string msg, int id) {
        std::lock_guard<std::mutex> locker(_mu);
        std::lock_guard<std::mutex> locker(_mu2)
        _f << "From " << id << ": " << value << endl;
    }
    void shared_print(string msg, int id) {
        std::lock_guard<std::mutex> locker(_mu2);
        std::lock_guard<std::mutex> locker(_mu)
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
