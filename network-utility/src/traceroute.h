#ifndef TRACEROUTE_H
#define TRACEROUTE_H

#include <string>
#include <vector>
#include "types/index.h"

class Traceroute {
public:
    Traceroute(const std::string& destination, int maxHops = 30, int timeout = 5);
    void start();
    std::string resolveHostname(const std::string& hostname);
    void printResults() const;

private:
    std::string destination;
    int maxHops;
    int timeout;
    std::vector<HopInfo> hops;

    HopInfo handleHop(int ttl);
};

#endif // TRACEROUTE_H