#ifndef CONFIG_H
#define CONFIG_H

// Default timeout for each hop in milliseconds
#define DEFAULT_TIMEOUT 1000

// Maximum number of hops to trace
#define MAX_HOPS 30

// Default network interface to use (empty string means system default)
#define DEFAULT_INTERFACE ""

// Default number of probes per hop
#define DEFAULT_PROBES 3

// Default TTL (Time to Live) value for packets
#define DEFAULT_TTL 64

// Enable or disable verbose output
#define ENABLE_VERBOSE_OUTPUT 0

#endif // CONFIG_H