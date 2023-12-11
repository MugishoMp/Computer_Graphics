#include <iostream>
#include "application.h"

int main() {
    try {
        Application app;
        app.Run();
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}