#ifndef TRACEROUTE_H
#define TRACEROUTE_H

#include <string>
#include <vector>
#include "types/index.h"

class Traceroute {
public:
    Traceroute(const std::string& hostname);
    void start();
    void resolveHostname();
    void printResults() const;

private:
    std::string hostname;
    std::vector<HopInfo> hops;
    static const int MAX_HOPS = 30;
    static const int TIMEOUT = 5; // in seconds

    void handleHop(int ttl);
    double measureRTT(int hopIndex);
};

#endif // TRACEROUTE_H