# Network Utility Diagnostic Tool

## Overview
This project is a diagnostic network utility for Linux that tracks packet routes in the network, similar to the `traceroute` command. It provides detailed information about each hop along the route to a specified destination, including round-trip time (RTT) measurements and hostname resolution.

## Features
- Tracks packet routes to a specified destination.
- Measures round-trip time (RTT) for each hop.
- Resolves hostnames for IP addresses encountered along the route.
- Configurable maximum hops and timeout values.
- Error handling for network operations.

## Project Structure
```
network-utility
├── src
│   ├── main.cpp               # Entry point of the utility
│   ├── traceroute.cpp         # Implementation of the Traceroute class
│   ├── traceroute.h           # Header file for the Traceroute class
│   ├── utils
│   │   ├── network_utils.cpp   # Utility functions for network operations
│   │   └── network_utils.h     # Header file for network utility functions
│   └── types
│       └── index.h            # Data structures and types used in the project
├── include
│   └── config.h               # Configuration settings for the utility
├── tests
│   ├── test_main.cpp          # Main function for running unit tests
│   ├── test_traceroute.cpp    # Unit tests for the Traceroute class
│   └── test_network_utils.cpp  # Unit tests for network utility functions
├── Makefile                    # Build instructions for the project
└── README.md                   # Documentation for the project
```

## Setup Instructions
1. Clone the repository:
   ```
   git clone <repository-url>
   cd network-utility
   ```

2. Build the project using the Makefile:
   ```
   make
   ```

3. Run the utility:
   ```
   ./network-utility <destination>
   ```

## Usage Example
To trace the route to a destination, use the following command:
```
./network-utility www.example.com
```

## Requirements
- Linux operating system
- C++11 or later
- Development tools (g++, make)

## Contributing
Contributions are welcome! Please submit a pull request or open an issue for any enhancements or bug fixes.

## License
This project is licensed under the MIT License. See the LICENSE file for more details.