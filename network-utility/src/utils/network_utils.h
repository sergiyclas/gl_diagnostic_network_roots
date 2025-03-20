#ifndef NETWORK_UTILS_H
#define NETWORK_UTILS_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <stdexcept>

int createRawSocket();
ssize_t sendPacket(int sockfd, const struct sockaddr_in &dest_addr, const char *packet, size_t packet_size);
ssize_t receivePacket(int sockfd, char *buffer, size_t buffer_size);

#endif // NETWORK_UTILS_H