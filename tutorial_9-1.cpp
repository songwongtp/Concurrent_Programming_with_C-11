/* Songwong Tasneeyapant
 * C++ Threading #9: packaged_task
*/

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
    std::thread t1(factorial, 6);
    std::packaged_task<int(int)> t(factorial);
    // t is a task being packaged
    // This package can be passed along to different places
    // (ie. different functions, different objects, different threads

    // cannot pass additional parameters as a parameters of the function
    // but we can use std::bind() function
    std::packaged_task<int()> t1(std::bind(factorial, 6));
        // bind function with parameters to create a function object
        // cannot take parameters anymore


    /// ... something happen

    t(6);   // executing task (need parameters) in a different context
            // cannot conveniently get the return value from t
            // t always returns
    int x = t.get_future().get();   // get the return value

    t1();

    return 0;
}
