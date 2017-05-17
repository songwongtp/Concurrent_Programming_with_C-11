/* Songwong Tasneeyapant
 * C++ Threading #10: Review and Time Constrain
*/

#include <iostream>
#include <thread>
#include <mutex>

int factorial(int N) {
    int res = 1;
    for(int i = N; i > 1; i--){
        res *= i;
    }
    cout << "Result is: " << res << endl;
    return res;
}

int main() {
    /* thread */
    std::thread t1(factorial, 6);

    std::this_thread::sleep_for(chrono::milliseconds(3));
    chrono::steady_clock::time_point tp = chrono::steady_clock:: now() + chrono::microseconds(4);
    std::this_thread::sleep_until(tp);


    /* Mutex */
    std::mutex mu;
    std::lock_guard<mutex> locker(mu);
    std::unique_lock<mutex> ulocker(mu);
        // unique_lock can lock/unlock a mutex for multiple times
        // it can also transfer an ownership of a mutex from one unique_lock to another

    ulocker.try_lock();
        // try to lock a mutex. If it is not successful, it will immediately return
    ulocker.try_lock_for(chrono::nanoseconds(500));
        // if 500 has passed and a mutex still cannot be locked, it will immediately return
    ulocker.try_lock_until(tp);


    /* Condition Variable */
    std::condition_variable cond;
        // Synchronize the execution order of threads

    cond.wait_for(ulocker, chrono::microseconds(2));
    cond.wait_until(ulocker, tp);


    /* Future and Promise */
    std::promise<int> p;
    std::future<int> f = p.get_future();
    f.get();

    f.wait();
        // wait for the data to be available ( get() will internally call wait() )
    f.wait_for(chrono::milliseconds(2));
    f.wait_until(tp);

    /* async() */
    std::future<int> fu = async(factorial, 6);
        // async can either spawn a child thread to run the function or run the function in the same thread

    /* Packaged Task */
    std::packaged_task<int(int)> t(factorial);
    std::future<int> fu2 = t.get_future();
    t(6);
        // a class template that can be parameterized the ways function signature of the task we are going to create

}
