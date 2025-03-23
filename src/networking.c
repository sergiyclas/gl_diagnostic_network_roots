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

#define TIMEOUT_SEC 0
#define TIMEOUT_MICROSEC 500000

int create_socket(struct sockaddr_in* dest_addr)
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
        int status;
        struct timeval timeout;
        timeout.tv_sec = TIMEOUT_SEC;
        timeout.tv_usec = TIMEOUT_MICROSEC;
        FD_ZERO(&fds);
        FD_SET(sock_fd, &fds);
        status = select(sock_fd+1, &fds, NULL, NULL, &timeout);
        if(status < 0)
        {
                perror("Error: timeout failed.");
                exit(1);
        }
        return !status;
}
