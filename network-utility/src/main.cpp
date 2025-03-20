#include <iostream>
#include "traceroute.h"

int main(int argc, char* argv[]) {
    // Check for command-line arguments
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <hostname>" << std::endl;
        return 1;
    }

    // Initialize the traceroute process
    Traceroute traceroute(argv[1]);

    // Start the traceroute
    traceroute.start();

    // Print the results
    traceroute.printResults();

    return 0;
}