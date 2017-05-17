/* Songwong Tasneeyapant
 * C++ Threading #2: Thread Management
*/

#include <iostream>
#include <thread>
using namespace std;

void function_1() {
    std::cout << "Beauty is only skin-deep" << std::endl;
}

class Fctor {
public:
    void operator()() {
        for(int i = 0; i > -100; i--){
            cout << "from t1 " << i << endl;
        }
    }
};

int main() {
    Fctor fct;
    //std::thread t1(fct); // should make a decision whether to join/detach t1
                           // before it goes out of scope
    std::thread t1((Fctor()));  //need () around Fctor() or else it will be considered
                                // as function decoration

    try {
        for(int i = 0; i < 100; i++){
            cout << "from main: " << i << endl;
        }
    } catch (...) {
        t1.join();  // to guarantee that t1 will be joined w/ or w/o execption
        throw;
    }
    t1.join();

    // Another approach
    // using RAII (Resource Acquisition is Initialization)
    // create a Wrapper class w(t1);
    // let destructor of the Wrapper class call t1.join() for us
    // so whenever w goes out of scope, it will automatically join the thread

    return 0;
}
