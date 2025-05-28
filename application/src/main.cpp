#include "application.h"
#include "exception_handling.h"

using App::Application;
using App::ErrorHandling::HandleCurrentException;

int main(int argc, char* argv[]) {
    try {
        Application app(argc, argv);
        app.run();
    } catch (...) {
        HandleCurrentException();
    }
    return 0;
}
