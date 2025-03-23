#include "fqdn.h"
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

void resolve_FQDN(char* FQDN, struct sockaddr_in* dest_addr, char* dest_addr_str, int dest_addr_str_size)
{
	// FQDN resolution
        struct addrinfo* result;
        int status = getaddrinfo(FQDN, NULL, NULL, &result);
        if(status != 0)
        {
                fprintf(stderr, "FQDN resolution error: %s\n", gai_strerror(status));
                exit(1);
        }

        struct addrinfo* p;
        struct sockaddr_in* ipv4;
        for(p = result; p != NULL; p = p->ai_next)
        {
                // The first entry with an IPv4 address for the provided FQDN
		if(p->ai_family == AF_INET)
                {
                        ipv4 = (struct sockaddr_in*)p->ai_addr;
                        dest_addr->sin_addr = ipv4->sin_addr;
                        break;
                }
                else
                {
                        continue;
                }
        }
        inet_ntop(p->ai_family, &ipv4->sin_addr, dest_addr_str, dest_addr_str_size);
        
        freeaddrinfo(result);
}

void reverse_FQDN_resolve(struct sockaddr* node_IP, int node_IP_size, char* FQDN, int FQDN_size)
{
        int status = getnameinfo(node_IP, node_IP_size, FQDN, FQDN_size, NULL, 0, NI_NAMEREQD);
        if(status != 0)
        {
                strcpy(FQDN, "Unknown");
        }
}
