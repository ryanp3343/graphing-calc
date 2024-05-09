#include <iostream>
#include "shuntingyard.h"
#include "user.h"
#include <string>
#include "queue.h"
#include "token.h"


int main() {
    try {
        user g;
        g.run();
    }
    catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1; // Return a non-zero value to indicate an error
    }
    return 0; // Indicate successful execution
}
