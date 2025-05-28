#include "exception_handling.h"

#include <exception>
#include <iostream>

namespace App {
namespace ErrorHandling {

void HandleCurrentException() {
    try {
        throw;
    } catch (std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Caught unknown exception" << std::endl;
    }
}

} // namespace ErrorHandling
} // namespace App
