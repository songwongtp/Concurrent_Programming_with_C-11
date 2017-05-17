/* Songwong Tasneeyapant
 * C++ Threading #7: Future, Promise and async()
*/

#include <iostream>
#include <future>

using namespace std;

// int factorial(std::future<int>& f) {
//     int res = 1;
//
//     int N = f.get();
//     for(int i = N; i > 1; i--){
//         res *= i;
//     }
//     cout << "Result is: " << res << endl;
//     return res;
// }

int factorial(std::shared_future<int> f) {
    int res = 1;

    int N = f.get();
    for(int i = N; i > 1; i--){
        res *= i;
    }
    cout << "Result is: " << res << endl;
    return res;
}

int main() {
    int x;
    // if the factorial needs to be computed many times
    // cannot pass the same future to all the threads, since each future can call get() only once

    std::promise<int> p;
    std::future<int> f = p.get_future();

    // Approach 1: create 10 futures
    // ...
    // std::future<int> fu = std::async(std::launch::async, factorial, std::ref(f));
    // std::future<int> fu2 = std::async(std::launch::async, factorial, std::ref(f));
    // std::future<int> fu3 = std::async(std::launch::async, factorial, std::ref(f
    // ... 10 threads

    // Approach 2: shared_future (unlike regular future, shared_future can be copied
    std::shared_future<int> sf = f.share();
    std::future<int> fu = std::async(std::launch::async, factorial, sf);


    p.set_value(4);

    return 0;
}
