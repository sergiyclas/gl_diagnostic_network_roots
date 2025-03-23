#ifndef CONSTRUCT_PACKET_H
#define CONSTRUCT_PACKET_H

#include <sys/socket.h>
#include <netinet/ip_icmp.h>

void construct_packet(int sock_fd, void* packet, int seq_number, int ttl, char* interface);

#endif
