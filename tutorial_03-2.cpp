/* Songwong Tasneeyapant
 * C++ Threading #3: Data Race and Mutex
*/

#include <iostream>
#include <thread>
#include <string>
#include <mutex>
using namespace std;

class LogFile {
    std::mutex m_mutex;
    ofstream f;

public:
    LogFile() {
        f.open("log.txt");
    } // Need destructor to close file
    void shared_print(string msg, int id) {
        std::lock_guard<std::mutex> guard(mu);
        f << "From " << id << ": " << value << endl;
    }
    // Never return f to the outside world
    ofstream& getStream() { return f; }
    // Never pass f as an argument to user provided function_1
    void processf(void fun(ofstream&)) {
        fun(f);
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
        log.shared_print(string("From main: "), i);
    }

    t1.join();

    return 0;
}
