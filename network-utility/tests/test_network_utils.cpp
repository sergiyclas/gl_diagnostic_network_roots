#include <gtest/gtest.h>
#include "network_utils.h"

TEST(NetworkUtilsTest, CreateRawSocket) {
    int sockfd = createRawSocket();
    EXPECT_GE(sockfd, 0) << "Failed to create raw socket";
    close(sockfd);
}

TEST(NetworkUtilsTest, SendPacket) {
    int sockfd = createRawSocket();
    struct sockaddr_in dest_addr;
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(0); // Port is not used for raw sockets
    dest_addr.sin_addr.s_addr = inet_addr("8.8.8.8"); // Example IP

    char packet[64] = {0}; // Example packet
    ssize_t sent_bytes = sendPacket(sockfd, packet, sizeof(packet), (struct sockaddr*)&dest_addr, sizeof(dest_addr));
    EXPECT_GT(sent_bytes, 0) << "Failed to send packet";
    
    close(sockfd);
}

TEST(NetworkUtilsTest, ReceivePacket) {
    int sockfd = createRawSocket();
    char buffer[1024];
    struct sockaddr_in src_addr;
    socklen_t addr_len = sizeof(src_addr);

    ssize_t received_bytes = receivePacket(sockfd, buffer, sizeof(buffer), (struct sockaddr*)&src_addr, &addr_len);
    EXPECT_GE(received_bytes, 0) << "Failed to receive packet";

    close(sockfd);
}