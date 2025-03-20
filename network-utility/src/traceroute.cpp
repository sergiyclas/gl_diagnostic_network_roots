#include <iostream>
#include <cstring>
#include <vector>
#include <chrono>
#include <thread>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "traceroute.h"
#include "utils/network_utils.h"
#include "types/index.h"

Traceroute::Traceroute(const std::string& destination, int maxHops, int timeout)
    : destination(destination), maxHops(maxHops), timeout(timeout) {}

void Traceroute::start() {
    for (int ttl = 1; ttl <= maxHops; ++ttl) {
        HopInfo hop = handleHop(ttl);
        hops.push_back(hop);
        if (hop.address == destination) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
    }
    printResults();
}

HopInfo Traceroute::handleHop(int ttl) {
    int sock = createRawSocket();
    if (sock < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return {};
    }

    setsockopt(sock, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));

    auto start = std::chrono::high_resolution_clock::now();
    sendPacket(sock, destination);
    HopInfo hop = receivePacket(sock);
    auto end = std::chrono::high_resolution_clock::now();

    close(sock);

    hop.rtt = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    return hop;
}

void Traceroute::printResults() {
    std::cout << "Traceroute to " << destination << ":\n";
    for (const auto& hop : hops) {
        std::cout << hop.ttl << " " << hop.address << " " << hop.rtt << " ms\n";
    }
}

std::string Traceroute::resolveHostname(const std::string& hostname) {
    struct sockaddr_in sa;
    inet_pton(AF_INET, hostname.c_str(), &(sa.sin_addr));
    return std::string(inet_ntoa(sa.sin_addr));
}