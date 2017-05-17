/* Songwong Tasneeyapant
 * C++ Threading #6: Condition Variable
*/

#include <iostream>
#include <thread>
#include <string>
#include <mutex>
using namespace std;

std::deque<int> q;
std::mutex mu;
std::condition_variable cond;

// produce of a data
void function_1() {
    int count = 10;
    while(count > 0) {
        std::unique_lock<mutex> locker(mu);
        q.push_front(count);
        locker.unlock();
        cond.notify_one(); // Notify one waiting thread, if there is one.

        //cond.notify_all(); // Notify all waiting threads at the same time

        std::this_thread::sleep_for(chrono::seconds(1)); // sleep for a second
        count--;
    }
}

// consume of a data
void function_2() {
    int data = 0;

    // Busy waiting is inefficient
    while(data != 1){
        std::unique_lock<mutex> locker(mu);
        // if(!q.empty()){
        //     data = q.back();
        //     q.pop_back();
        //     locker.unlock();
        //     cout << "t2 got a value from t1: " << data << endl;
        // } else {
        //     locker.unlock();
        //
        //     // let the thread to take a nap to reduce the number of looping
        //     std::this_thread::sleep_for(chrono::milliseconds(10));
        //     // But what time duration should be used
        //     // Too short, still end up spends a lot of time looping
        //     // Too long, might not get the data in time
        // }

        cond.wait(locker, [](){ return !q.empty();} );
                            // unlock the locker before going to sleep
                            // lock the locker again, then unlock when everything is finish
                            // Need to use unique_lock, since we have to lock/unlock many times

                            // spurious wake (thread2 can also wake up by itself)
                            // set a second parameter (in this case a lambda function)
                            // if the queue is empty, it will go back to sleep again
                            // otherwise, it will pop out a data
        data = q.back();
        q.pop_back();
        locker.unlock();
        cout << "t2 got a value from t1: " << data << endl;
    }
}

int main() {
    std::thread t1(function_1);
    std::thread t2(function_2);
    t1.join();
    t2.join();
    return 0;
}
