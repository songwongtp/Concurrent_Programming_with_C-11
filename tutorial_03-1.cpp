/* Songwong Tasneeyapant
 * C++ Threading #3: Data Race and Mutex
*/

#include <iostream>
#include <thread>
#include <string>
#include <mutex>
using namespace std;

std::mutex mu;

void shared_print(string msg, int id) {
    //mu.lock(); // if cout throw an exception, the mutex will be locked forever
    std::lock_guard<std::mutex> guard(mu);  // RAII
    cout << msg << id << endl;  // still cout is not locked completely
                                // it can still be called by other threads
                                // see how to fix in tutorial_3-2.cpp
    //mu.unlock();
}

void function_1() {
    for(int i = 0; i > -100; i--){
        shared_print(string("From t1: "), i);
        // Race Condition
        //  an outcome of the program depends on a relative execution order of
        //  one or more threads
    }
}

int main() {
    std::thread t1(function_1);

    for(int i = 0; i < 100; i++){
        shared_print(string("From main: "), i);
    }

    t1.join();

    return 0;
}
