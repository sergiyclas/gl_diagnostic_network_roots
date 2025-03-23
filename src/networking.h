#ifndef NETWORKING_H
#define NETWORKING_H

#include <sys/socket.h>
#include <netinet/in.h>

int create_socket(struct sockaddr_in* dest_addr);
void send_packet(int sock_fd, const void* packet, int packet_size, struct sockaddr* dest, int dest_size);
void recv_packet(int sock_fd, char* rcvd_msg, int rcvd_msg_size, struct sockaddr* node_IP, unsigned int* node_IP_size);
int packet_timed_out(int sock_fd);

#endif
