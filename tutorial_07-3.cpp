/* Songwong Tasneeyapant
 * C++ Threading #7: Future, Promise and async()
*/

#include <iostream>
#include <future>

using namespace std;

int factorial(std::future<int>& f) {
    int res = 1;

    int N = f.get();    // exception: std::future_errc::broken_promise
    for(int i = N; i > 1; i--){
        res *= i;
    }
    cout << "Result is: " << res << endl;
    return res;
}

int main() {
    int x;

    // promise & future cannot be copied
    std::promise<int> p;
    // std::promise<int> p2 = p; will not compile
    // std::promise<int> p2 = std::move(p) will compile

    std::future<int> f = p.get_future();

    // will send a value to a child thread in the future
    std::future<int> fu = std::async(std::launch::async, factorial, std::ref(f));

    // do something else
    std::this_thread::sleep_for(chrono::milliseconds(20));

    // forget the promise to send the child thread a value or broken the promise
    // p.set_value(4);
    //
    // x = fu.get();
    // cout << "Get from child: " << x << endl;

    // So you have to send a value
    // if you know you cannot send a value, use
    p.set_exception(std::make_exception_ptr(std::runtime_error("To err is human")));

    return 0;
}
