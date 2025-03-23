#ifndef FQDN_H
#define FQDN_H

#include <sys/socket.h>
#include <netinet/in.h>

void resolve_FQDN(char* FQDN, struct sockaddr_in* dest_addr, char* dest_addr_str, int dest_addr_str_size);
void reverse_FQDN_resolve(struct sockaddr* node_IP, int node_IP_size, char* FQDN, int FQDN_size);

#endif
