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
        if (hop.ipAddress == destination) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
    }
}

HopInfo Traceroute::handleHop(int ttl) {
    int sock = createRawSocket();
    if (sock < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return HopInfo(ttl, "", "", 0.0);
    }

    setsockopt(sock, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));

    char packet[64] = {0}; // Example packet
    struct sockaddr_in dest_addr;
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = inet_addr(destination.c_str());

    auto start = std::chrono::high_resolution_clock::now();
    sendPacket(sock, dest_addr, packet, sizeof(packet));
    char buffer[1024];
    struct sockaddr_in src_addr;
    socklen_t addr_len = sizeof(src_addr);
    ssize_t received_bytes = receivePacket(sock, buffer, sizeof(buffer));
    auto end = std::chrono::high_resolution_clock::now();

    close(sock);

    double rtt = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::string ipAddress = inet_ntoa(src_addr.sin_addr);
    std::string hostname = resolveHostname(ipAddress);

    return HopInfo(ttl, ipAddress, hostname, rtt);
}

void Traceroute::printResults() const {
    std::cout << "Traceroute to " << destination << ":\n";
    for (const auto& hop : hops) {
        std::cout << hop.hopNumber << " " << hop.ipAddress << " " << hop.rtt << " ms\n";
    }
}

std::string Traceroute::resolveHostname(const std::string& hostname) {
    struct sockaddr_in sa;
    inet_pton(AF_INET, hostname.c_str(), &(sa.sin_addr));
    return std::string(inet_ntoa(sa.sin_addr));
}