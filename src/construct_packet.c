#include "construct_packet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip_icmp.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "checksum.h"

#define ICMP_BUFF 40 // ICMP header size(8) + the payload(32)

void construct_packet(int sock_fd, void* packet, int seq_number, int ttl, char* interface)
{
        struct icmphdr icmp_hdr = {0};
        char* payload = "abcdefghijklmnopqrstuvwxyz012345";

        if(interface != NULL)
        {
                if(setsockopt(sock_fd, SOL_SOCKET, SO_BINDTODEVICE, interface, strlen(interface)) != 0)
                {
                        perror("Error: binding socket to interface failed.");
                        exit(1);
                }
        }

        setsockopt(sock_fd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));

        memcpy(packet, &icmp_hdr, sizeof(struct icmphdr));
        memcpy(packet+sizeof(struct icmphdr), payload, strlen(payload));
        struct icmphdr* icmp_hdr_ptr = (struct icmphdr*)packet;

        // ICMP header initialization
        icmp_hdr_ptr->type = ICMP_ECHO;
        icmp_hdr_ptr->code = 0;
        icmp_hdr_ptr->un.echo.id = getpid();
        icmp_hdr_ptr->un.echo.sequence = seq_number;
        icmp_hdr_ptr->checksum = 0;
        icmp_hdr_ptr->checksum = checksum((unsigned short*)packet, ICMP_BUFF);
}
