# gl_diagnostic_network_roots

## Description

This is a simple traceroute tool implemented in C. It allows you to trace the route packets take to reach a destination host, similar to the standard `traceroute` utility.

## Features

*   **Traces the route to a destination:** Determines the path taken by packets to reach a specified destination.
*   **Customizable maximum hops:** Limits the maximum number of hops to trace.
*   **Customizable timeout:** Sets a timeout for receiving responses from intermediate nodes.
*   **Interface selection:** Allows specifying a particular network interface to use for sending packets.
*   **Built-in FQDN resolution:** Resolves the provided FQDN to an IP address.
*   **Reverse FQDN resolution:** Attempts to resolve IP addresses of intermediate nodes to FQDNs.

## Installation and Compilation

### For Linux
To download and compile the program:

1.  Download the repository using git:

```bash
git clone https://github.com/sergiyclas/gl_diagnostic_network_roots
cd gl_diagnostic_network_roots
```

2.  Compile the program using the provided `Makefile`:

```bash
make
```

This will create an executable named `rooter` in the project directory.

### For OpenWRT
To build rooter as a native .ipk package for OpenWRT:

1. Download the repository using git:

```bash
git clone https://github.com/sergiyclas/gl_diagnostic_network_roots
cd gl_diagnostic_network_roots
```

2. Download and extract the official OpenWRT SDK for your target platform(example: openwrt-sdk-23.05.2-x86-64):
```bash
wget https://downloads.openwrt.org/releases/23.05.2/targets/x86/64/openwrt-sdk-23.05.2-x86-64_gcc-12.3.0_musl.Linux-x86_64.tar.xz
tar -xf openwrt-sdk-23.05.2-x86-64_gcc-12.3.0_musl.Linux-x86_64.tar.xz
cd openwrt-sdk-23.05.2-x86-64_gcc-12.3.0_musl.Linux-x86_64
```
3. Copy the OpenWRT/Makefile and src directory into the openwrt-sdk*/package/rooter directory (openwrt-sdk* -> root directory OpenWRT SDK). 
4. Launch menuconfig and enable the package:
```bash
make menuconfig
# Navigate to: Utilities → search "rooter" → there must be "M" or "*" to the left of the package
```
5. Compile only the rooter package(in the OpenWRT root directory):
```bash
make package/rooter/compile
```
6. After a successful build, you can find the .ipk in:

`bin/packages/<version of OpenWRT>/base/rooter_1.0-1_<version of OpenWRT>.ipk`


## Usage

```bash
sudo ./traceroute [-m max_hops] [-t timeout_sec] [-i interface] <Destination FQDN>
```

*   `-m max_hops`: Specifies the maximum number of hops (default: 30).
*   `-t timeout_sec`: Specifies the timeout in seconds for waiting for a response (no timeout if not specified).
*   `-i interface`: Specifies the network interface to use.
*   `<Destination FQDN>`: The fully qualified domain name of the destination host.

**Example:**

```bash
sudo ./traceroute -m 20 -t 2 -i eth0 example.com
```

This command will trace the route to `example.com`, with a maximum of 20 hops, a timeout of 2 seconds, using the `eth0` interface.

## Files

*   `Makefile`:  Build configuration file.
*   `README.md`:  This file.
*   `src/`: Source code directory.
    *   `checksum.c`:  Implementation of the IP checksum calculation.
    *   `checksum.h`:  Header file for `checksum.c`.
    *   `construct_packet.c`:  Implementation for constructing ICMP packets.
    *   `construct_packet.h`:  Header file for `construct_packet.c`.
    *   `fqdn.c`:  Implementation for FQDN resolution and reverse resolution.
    *   `fqdn.h`:  Header file for `fqdn.c`.
    *   `main.c`:  Main program file, containing the `main` function.
    *   `networking.c`:  Implementation of networking functions (socket creation, sending/receiving packets, etc.).
    *   `networking.h`:  Header file for `networking.c`.
*   `test/`: Test script directory.
    *   `test_file.sh`: A bash script to compare original function `traceroute` with custom `traceroute`.

## Dependencies

*   Standard C libraries
*   `getopt.h` (for argument parsing)

## Building for OpenWRT

The `Makefile` also supports building for OpenWRT. To build for OpenWRT, you need to have the OpenWRT build environment set up.

1.  Copy the project directory to the `package/` directory in your OpenWRT build environment.
2.  Run `make menuconfig` in your OpenWRT build environment and select the `traceroute` package under the "Utilities" menu.
3.  Run `make package/traceroute/compile` to compile the package.
4.  The compiled package will be available in the `bin/packages` directory.

## Notes

*   This tool requires root privileges to create raw sockets.
*   The timeout value is approximate and may vary depending on network conditions.
*   Reverse FQDN resolution may not always be successful.
