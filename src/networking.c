#include "networking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <ifaddrs.h>

int create_socket(struct sockaddr_in* dest_addr, char* interface)
{
    // Socket creation
    int sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if(sock_fd < 0)
    {
        perror("Error: Failed to initialize socket.");
        exit(1);
    };

    // Socket configuring
    dest_addr->sin_family = AF_INET;
    dest_addr->sin_port = 0;

    if (interface != NULL) {
        if (setsockopt(sock_fd, SOL_SOCKET, SO_BINDTODEVICE, interface, strlen(interface)) < 0) {
            perror("Error: Failed to bind to interface");
            close(sock_fd);
            exit(1);
        }
    }

    return sock_fd;
}

void send_packet(int sock_fd, const void* packet, int packet_size, struct sockaddr* dest, int dest_size)
{
    int data_sent = sendto(sock_fd, packet, packet_size, 0, (struct sockaddr *)dest, dest_size);
    if(data_sent < 0)
    {
        perror("Error: sending data failed.");
        exit(1);
    }
}

void recv_packet(int sock_fd, char* rcvd_msg, int rcvd_msg_size, struct sockaddr* node_IP, unsigned int* node_IP_size)
{
    int data_recvd = recvfrom(sock_fd, rcvd_msg, rcvd_msg_size, 0, node_IP, node_IP_size);
    if(data_recvd < 0)
    {
        perror("Error: receiving data failed.");
        exit(1);
    }
}

int packet_timed_out(int sock_fd)
{
    fd_set fds;
    struct timeval timeout;
    int status;

    FD_ZERO(&fds);
    FD_SET(sock_fd, &fds);

    timeout.tv_sec = 0;
    timeout.tv_usec = 500000;

    status = select(sock_fd+1, &fds, NULL, NULL, &timeout);
    if(status < 0)
    {
        perror("Error: select failed");
        exit(1);
    }

    return !status;
}

void set_socket_timeout(int sock_fd, int timeout_sec, int timeout_usec) {
    struct timeval timeout;
    timeout.tv_sec = timeout_sec;
    timeout.tv_usec = timeout_usec;

    if (setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) < 0) {
        perror("setsockopt(SO_RCVTIMEO) failed");
        exit(1);
    }
}
