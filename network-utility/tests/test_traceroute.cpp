#include "gtest/gtest.h"
#include "traceroute.h"
#include <sstream>

class TracerouteTest : public ::testing::Test {
protected:
    TracerouteTest() : traceroute("example.com") {}
    Traceroute traceroute;
};

TEST_F(TracerouteTest, TestResolveHostname) {
    std::string ipAddress = traceroute.resolveHostname("example.com");
    ASSERT_NE(ipAddress, "0.0.0.0");
}

TEST_F(TracerouteTest, TestStartWithValidDestination) {
    std::string destination = "example.com";
    EXPECT_NO_THROW(traceroute.start());
}

TEST_F(TracerouteTest, TestStartWithInvalidDestination) {
    std::string destination = "invalid_destination";
    EXPECT_THROW(traceroute.start(), std::runtime_error);
}

TEST_F(TracerouteTest, TestPrintResults) {
    std::string destination = "example.com";
    traceroute.start();
    std::ostringstream output;
    traceroute.printResults();
    ASSERT_FALSE(output.str().empty());
}