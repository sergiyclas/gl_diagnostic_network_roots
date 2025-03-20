#ifndef NETWORK_UTILITY_TYPES_INDEX_H
#define NETWORK_UTILITY_TYPES_INDEX_H

#include <string>
#include <vector>

struct HopInfo {
    int hopNumber;
    std::string ipAddress;
    std::string hostname;
    double rtt; // Round Trip Time in milliseconds

    HopInfo(int number, const std::string& ip, const std::string& host, double roundTripTime)
        : hopNumber(number), ipAddress(ip), hostname(host), rtt(roundTripTime) {}
};

using Route = std::vector<HopInfo>;

#endif // NETWORK_UTILITY_TYPES_INDEX_H