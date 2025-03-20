#include "network_utils.h"
#include <sys/socket.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>
#include <iostream>

int createRawSocket() {
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock < 0) {
        std::cerr << "Failed to create raw socket" << std::endl;
    }
    return sock;
}

ssize_t sendPacket(int sockfd, const struct sockaddr_in &dest_addr, const char *packet, size_t packet_size) {
    ssize_t bytes_sent = sendto(sockfd, packet, packet_size, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    if (bytes_sent < 0) {
        std::cerr << "Error sending packet: " << strerror(errno) << std::endl;
    }
    return bytes_sent;
}

ssize_t receivePacket(int sockfd, char *buffer, size_t buffer_size) {
    ssize_t bytes_received = recv(sockfd, buffer, buffer_size, 0);
    if (bytes_received < 0) {
        std::cerr << "Error receiving packet: " << strerror(errno) << std::endl;
    }
    return bytes_received;
}