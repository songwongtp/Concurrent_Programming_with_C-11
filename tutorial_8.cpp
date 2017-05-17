/* Songwong Tasneeyapant
 * C++ Threading #8: Using Callable Objects
*/

#include <thread>

class A {
public:
    void f(int x, char c) {}
    long g(double x) { return 0; }
    int operator()(int N) { return 0; }
}

void foo(int x) {}

int main() {
    A a;
    std::thread t1(a, 6);
        // use copy_of_a() as a functor in a different thread
    std::thread t2(std::ref(a), 6);
        // use a() as a functor in a different thread
    std::thread t3(std::move(a), 6);
        // a is no longer usable in main thread
    std::thread t4(A(), 6);
        // use a temporary_a() in a different thread
    std::thread t5([](int x){ return x*x; }, 6);
        // a lambda function that takes an integer parameter
    std::thread t6(foo, 7);

    std::thread t7(&A::f, a, 8, 'w');
        // a thread with a member function
        // a copy_of_a.f(8, 'w') in a different thread
    std::thread t8(&A::f, &a, 8, 'w');
        // a a.f(8, 'w') in a different thread

    // these ways of using callable objects can also be used with
    // std::bind(); std::async(); std::call_once();
    std::async(std::launch::async, a, 6);
    std::bind(a, 6);
    std::call_once(once_flag, a, 6);

    return 0;
}
