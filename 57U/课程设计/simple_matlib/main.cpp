#include "Interface.h"
using namespace std;

int main(const int argc, char* argv[]) {
    Interface interface;

    if (Utils::isContain(argv+1,argc-1,"debug")) {
        interface.debug=true;
        cout<<"debug enabled"<<endl;
    }
    if (Utils::isContain(argv+1,argc-1,"nogc")) {
        interface.gcEnabled=false;
        cout<<"gc disabled"<<endl;
    }
    interface.startEventLoop();
    return 0;
}
