# CMake generated Testfile for 
# Source directory: C:/My_deals/Linux/GL/diagnostic_network_manager/gl_diagnostic_network_roots/network-utility
# Build directory: C:/My_deals/Linux/GL/diagnostic_network_manager/gl_diagnostic_network_roots/network-utility/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(NetworkUtilsTest "C:/My_deals/Linux/GL/diagnostic_network_manager/gl_diagnostic_network_roots/network-utility/build/Debug/test_network_utility.exe")
  set_tests_properties(NetworkUtilsTest PROPERTIES  _BACKTRACE_TRIPLES "C:/My_deals/Linux/GL/diagnostic_network_manager/gl_diagnostic_network_roots/network-utility/CMakeLists.txt;39;add_test;C:/My_deals/Linux/GL/diagnostic_network_manager/gl_diagnostic_network_roots/network-utility/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(NetworkUtilsTest "C:/My_deals/Linux/GL/diagnostic_network_manager/gl_diagnostic_network_roots/network-utility/build/Release/test_network_utility.exe")
  set_tests_properties(NetworkUtilsTest PROPERTIES  _BACKTRACE_TRIPLES "C:/My_deals/Linux/GL/diagnostic_network_manager/gl_diagnostic_network_roots/network-utility/CMakeLists.txt;39;add_test;C:/My_deals/Linux/GL/diagnostic_network_manager/gl_diagnostic_network_roots/network-utility/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(NetworkUtilsTest "C:/My_deals/Linux/GL/diagnostic_network_manager/gl_diagnostic_network_roots/network-utility/build/MinSizeRel/test_network_utility.exe")
  set_tests_properties(NetworkUtilsTest PROPERTIES  _BACKTRACE_TRIPLES "C:/My_deals/Linux/GL/diagnostic_network_manager/gl_diagnostic_network_roots/network-utility/CMakeLists.txt;39;add_test;C:/My_deals/Linux/GL/diagnostic_network_manager/gl_diagnostic_network_roots/network-utility/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(NetworkUtilsTest "C:/My_deals/Linux/GL/diagnostic_network_manager/gl_diagnostic_network_roots/network-utility/build/RelWithDebInfo/test_network_utility.exe")
  set_tests_properties(NetworkUtilsTest PROPERTIES  _BACKTRACE_TRIPLES "C:/My_deals/Linux/GL/diagnostic_network_manager/gl_diagnostic_network_roots/network-utility/CMakeLists.txt;39;add_test;C:/My_deals/Linux/GL/diagnostic_network_manager/gl_diagnostic_network_roots/network-utility/CMakeLists.txt;0;")
else()
  add_test(NetworkUtilsTest NOT_AVAILABLE)
endif()
