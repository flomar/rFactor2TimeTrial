// main.cpp

#include <application.h>

int main(int _argc, char **_argv) {
    Application application(_argc, _argv);
    // try to initialize the application
    if(!application.initialize()) {
        return -1;
    }
    // execute the application
    const int result = application.exec();
    // try to deinitialize the application
    if(!application.deinitialize()) {
        return -1;
    }
    return result;
}
