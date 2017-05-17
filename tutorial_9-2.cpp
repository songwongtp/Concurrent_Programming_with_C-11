/* Songwong Tasneeyapant
 * C++ Threading #9: packaged_task
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

std::deque<std::packaged_task<int()> > task_q;
std::mutex mu;
std::condition_variable cond;

void thread_1() {
    std::packaged_task<int()> t;
    {
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker, [](){ return !task_q.empty() });
            // to guarantee that task_q is not empty
        t = std::move(task_q.front());
        task_q.pop_front();
    }
    t();
}

int main() {
    std::thread t1(thread_1);

    // the important of packaged_task is that it can link the callable object to a future
    // which is very important in a threading environment
    std::packaged_task<int()> t(std::bind(factorial, 6));
    std::future<int> fu = t.get_future();
    {
        // task_q is shared between main and thread_1, so we have a data race condition
        // so we need a mutex
        std::lock_guard<std::mutex> locker(mu);
        task_q.push_back(std::move(t)); // we can move t, since t is no longer used in the main thread
    }
    cond.notify_one();

    cout << fu.get();


    t1.join();
    return 0;
}
