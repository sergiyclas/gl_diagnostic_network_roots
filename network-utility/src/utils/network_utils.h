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
ssize_t sendPacket(int socket, const std::string& destination, const void* packet, size_t packetSize);
ssize_t receivePacket(int socket, void* buffer, size_t bufferSize, struct sockaddr_in* senderAddr);

#endif // NETWORK_UTILS_H