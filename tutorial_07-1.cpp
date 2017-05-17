/* Songwong Tasneeyapant
 * C++ Threading #7: Future, Promise and async()
*/

#include <iostream>
#include <future>

using namespace std;

// std::mutex mu;
// std::condition_variable cond;
//
// void factorial(int N, int &x) {
//     int res = 1;
//     for(int i = N; i > 1; i--){
//         res *= i;
//     }
//
//     cout << "Result is: " << res << endl;
//     x = res;
// }

int factorial(int N) {
    int res = 1;
    for(int i = N; i > 1; i--){
        res *= i;
    }
    cout << "Result is: " << res << endl;
    return res;
}

int main() {
    int x;
    // instead of passing x by reference with mutex to lock x and condition_variable
    //std::thread t1(factorial, 4, std::ref(x));
    //t1.join();

    // std::future<int> fu = std::async(factorial, 4); // async may/may not create another thread
    // std::future<int> fu = std::async(std::launch::deferred, factorial, 4);
        // defer the execution of factorial function until the get() is called
        // when the get() function is called, the factorial function will be executed in the same thread
    std::future<int> fu = std::async(std::launch::async, factorial, 4);
        // create another thread
    // std::future<int> fu = std::async(std::launch::async | std::launch::deferred, factorial, 4);
        // whether an async function will create another thread or not
        // will be determined by the implementation
        // (a default value)

    x = fu.get(); // fu.get() will wait till a child thread finish
                  // then return the value from the child thread
                  // Can be called only once

    //x = fu.get() // crash the program

    return 0;
}
