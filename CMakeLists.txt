cmake_minimum_required(VERSION 3.21)
project(Hello_server C)

set(CMAKE_C_STANDARD 99)

add_executable(Hello_server Hello_server/hello_server.c)
add_executable(Hello_client Hello_server/hello_client.c)

add_executable(udp_echo_server udp/echo_server.c)
add_executable(udp_echo_client udp/echo_client.c)
add_executable(udp_bound_host1 udp/bound_host1.c)
add_executable(udp_bound_host2 udp/bound_host2.c)
add_executable(udp_echo_con_client udp/echo_con_client.c)
add_executable(Basic_Socket_tcp_server Basic_Socket/tcp_server.c)
add_executable(Basic_Socket_tcp_client Basic_Socket/tcp_client.c)