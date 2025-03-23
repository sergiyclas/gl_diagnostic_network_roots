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
#include "networking.h"
#include "fqdn.h"
#include "construct_packet.h"

#define DEST_IP_BUFF 100
#define SRC_IP_BUFF 100
#define ICMP_BUFF 40 // ICMP header size(8) + the payload(32)
#define RCVD_MSG_BUFF 512
#define FQDN_BUFF 512
#define MAX_HOPS 30
#define PACKETS_PER_TTL 3

int main(int argc, char* argv[])
{
	char dest_IP_str[DEST_IP_BUFF];
        char src_IP_str[SRC_IP_BUFF]; 
        char packet[ICMP_BUFF]; // ICMP packet buffer(IPv4 payload)
        char rcvd_msg[RCVD_MSG_BUFF];
        char FQDN[FQDN_BUFF]; 
        char* interface = (argc > 2) ? argv[2] : NULL; 
        struct sockaddr_in dest_IP; 
        struct sockaddr_in node_IP;
        struct timeval time_start;
        struct timeval time_end;
        unsigned int node_IP_size = sizeof(node_IP);
        unsigned int dest_IP_size = sizeof(dest_IP);
        int sock_fd; 
        int ttl = 1; // IPv4 time to live
        int seq_number = 1; // ICMP sequence number
        int first_reply = 1; // To print FQDN and IP address of an intermediate node just once
        int line_overflow = 0; // To keep track of how many packets per TTL value is sent
        long double rtt; // Round trip time

        if(argc > 3 || argc < 2)
        {
                fprintf(stderr, "Usage: %s <Destination FQDN> [interface]\n", argv[0]);
                exit(1);
        }

	resolve_FQDN(argv[1], &dest_IP, dest_IP_str, sizeof(dest_IP_str));
        printf("Destination ip: %s, %d hops max\n", dest_IP_str, MAX_HOPS);

        sock_fd = create_socket(&dest_IP);
        while(ttl <= MAX_HOPS)
        {
                printf("%d.\t Reply from ", ttl);
                for(line_overflow = 0; line_overflow < PACKETS_PER_TTL; line_overflow++)
                {
                        construct_packet(sock_fd, packet, seq_number, ttl, interface);
                        gettimeofday(&time_start, NULL);
                        send_packet(sock_fd, packet, sizeof(packet), (struct sockaddr*)&dest_IP, dest_IP_size);
                        if(packet_timed_out(sock_fd))
                        {
                                printf("* ");
                        }
                        else
                        {
                                recv_packet(sock_fd, rcvd_msg, sizeof(rcvd_msg), (struct sockaddr*)&node_IP, &node_IP_size);
                                gettimeofday(&time_end, NULL);
                                rtt = ((long double)time_end.tv_sec - (long double)time_start.tv_sec)*1000.0 + ((long double)time_end.tv_usec - (long double)time_start.tv_usec)/1000;
                                reverse_FQDN_resolve((struct sockaddr*)&node_IP, sizeof(node_IP), FQDN, sizeof(FQDN));
                                strcpy(src_IP_str, inet_ntoa(node_IP.sin_addr));
                                if(first_reply)
                                {
                                        printf("%s (%s) ", FQDN, src_IP_str);
                                        first_reply = 0;
                                }
                                printf("%.3Lf ms ", rtt);
                        }
                        seq_number++;
                }
                printf("\n");
                first_reply = 1;

                if(memcmp(&dest_IP.sin_addr, &node_IP.sin_addr, sizeof(dest_IP.sin_addr)) == 0)        
                {
                        break;
                }
                ttl++;
        }
        close(sock_fd);

	return 0;
}
