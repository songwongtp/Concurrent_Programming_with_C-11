/* Songwong Tasneeyapant
 * C++ Threading #2: Thread Management
*/

#include <iostream>
#include <thread>
using namespace std;

class Fctor {
public:
    void operator()(string& msg) {  // parameter is still passed by value
                                    // parameters to a thread are always passed by value
                                    // or use std::ref()
        cout << "t1 says: " << msg << endl;
        msg = "Trust is the mother of deceit.";
    }
};

int main() {
    string s = "Where there is no trust, there is no love";
    cout << std::this_thread::get_id() << endl; // main thread's id


    // (useful guide for splitting task among threads)
    std::thread::hardware_concurrency();    // give an indication of how many threads
                                            // can be truly running concurrently
                                            // for this program
                                            // Eg. it might give the number of CPU cores


    //std::thread t1((Fctor()), std::ref(s)); // make s to be passed by ref

    // another method => pointer
    std::thread t1((Fctor()), std::move(s));
    cout << t1.get_id() << endl;
        // move s from the main thread to the child thread
        // both safe & efficient

    //some certain object in C++ can only be moved, not copied. Eg. thread
    // std::thread t2 = t1; cannot be compiled
    std::thread t2 = std::move(t1);
    t2.join(); // has to use t2, since t1 is empty now

    cout << "from main: " << s << endl;

    return 0;
}
