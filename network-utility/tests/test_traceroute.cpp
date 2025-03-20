#include <gtest/gtest.h>
#include "../src/traceroute.h"

class TracerouteTest : public ::testing::Test {
protected:
    Traceroute traceroute;

    void SetUp() override {
        // Initialize traceroute with default parameters if needed
    }

    void TearDown() override {
        // Clean up resources if needed
    }
};

TEST_F(TracerouteTest, TestResolveHostname) {
    std::string hostname = "www.example.com";
    std::string resolvedIP = traceroute.resolveHostname(hostname);
    EXPECT_FALSE(resolvedIP.empty());
}

TEST_F(TracerouteTest, TestStartWithValidDestination) {
    std::string destination = "8.8.8.8"; // Google's public DNS
    EXPECT_NO_THROW(traceroute.start(destination));
}

TEST_F(TracerouteTest, TestStartWithInvalidDestination) {
    std::string destination = "invalid.host";
    EXPECT_THROW(traceroute.start(destination), std::runtime_error);
}

TEST_F(TracerouteTest, TestPrintResults) {
    std::string destination = "8.8.8.8";
    traceroute.start(destination);
    std::ostringstream output;
    traceroute.printResults(output);
    EXPECT_FALSE(output.str().empty());
}