/* Songwong Tasneeyapant
 * C++ Threading #1: Introduction
*/

#include <iostream>
#include <thread>
using namespace std;

void function_1() {
    std::cout << "Beauty is only skin-deep" << std::endl;
}

int main() {
    std::thread t1(function_1); // t1 starts running
    //t1.join();  // main thread waits for t1 to finish

    t1.detach();// t1 will run freely on its own -- daemon process
                // Since the main thread is no longer connected
                // C++ runtime library is responsible for reclaiming resources of t1

                // In this case, the main thread will finish before t1 even
                // has a chance to deliver a message to stdout

                // If two threads are sharing certain resource (in this case "stdout")
                // the thread that owns that resource (in this case "main thread")
                // should have live as long as the other thread is accessing the resource

    // You can join()/detach() only once
    // once detach, forever detach (cannot join after that)
    if(t1.joinable()){
        t1.join();  // still cannot join, but the program will not crash
    }

    return 0;
}
