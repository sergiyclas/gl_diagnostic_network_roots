#include <gtest/gtest.h>
#include "utils/network_utils.h"
#include <cstring>
#include <arpa/inet.h>

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
    ssize_t sent_bytes = sendPacket(sockfd, dest_addr, packet, sizeof(packet));
    EXPECT_GT(sent_bytes, 0) << "Failed to send packet";

    close(sockfd);
}

TEST(NetworkUtilsTest, ReceivePacket) {
    int sockfd = createRawSocket();
    char buffer[1024];

    // Bind the socket to a known address and port
    struct sockaddr_in local_addr;
    memset(&local_addr, 0, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = INADDR_ANY;
    local_addr.sin_port = htons(12345); // Example port

    if (bind(sockfd, (struct sockaddr*)&local_addr, sizeof(local_addr)) < 0) {
        close(sockfd);
        FAIL() << "Failed to bind socket";
    }

    // Send a dummy packet to the socket so that we can receive it
    struct sockaddr_in dest_addr;
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    dest_addr.sin_port = htons(12345);

    char dummy_packet[64] = "test";
    sendto(sockfd, dummy_packet, sizeof(dummy_packet), 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr));

    ssize_t received_bytes = receivePacket(sockfd, buffer, sizeof(buffer));
    EXPECT_GE(received_bytes, 0) << "Failed to receive packet";

    close(sockfd);
}