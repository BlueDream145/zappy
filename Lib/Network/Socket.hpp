/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Socket
*/

#pragma once

// std::runtime_error
#include <stdexcept>
// std::string
#include <string>
// strerror
#include <string.h>

extern "C" {
    #include "socket.h"
}

/* Header only C++ Wrapper for Network C library */
namespace net { class Socket; }

class net::Socket
{
public:
    Socket(void) { assertC(init_socket(&_s)); }
    Socket(const socket_t &socket) : _s(socket) {}
    ~Socket(void) { clear(); }

    /* Getters */
    int fd(void) const noexcept { return _s.fd; }
    const char *buffer(void) const noexcept { return _s.buffer; }
    const char *ip(void) const noexcept { return _s.ip; }
    port_t port(void) const noexcept { return _s.port; }

    /* Helper */
    void initAsServer(const std::string &ip, port_t port, int count = 3) {
        assertC(init_server_socket(&_s, ip.c_str(), port, count));
    }
    void initAsClient(const std::string &ip, port_t port) {
        assertC(init_client_socket(&_s, ip.c_str(), port));
    }

    /* Setup */
    void open(void) {
        assertC(open_socket(&_s));
    }
    void setOpt(void) {
        assertC(set_socket_opt(&_s));
    }
    void listen(int count = 3) {
        assertC(listen_socket(&_s, count));
    }
    void setBlocking(bool value) {
        set_socket_blocking(&_s, value);
    }
    void clear(void) {
        clear_socket(&_s);
    }

    /* Connexion */
    void bind(const std::string &ip, port_t port) {
        assertC(bind_socket(&_s, ip.c_str(), port));
    }
    bool accept(Socket &socket) {
        socket = accept_socket(&_s);
        return socket.fd() != -1;
    }
    void connect(const std::string &ip, port_t port) {
        return assertC(connect_socket(&_s, ip.c_str(), port));
    }

    /* Stream */
    bool read(std::string &target) {
        if (!read_socket(&_s))
            return false;
        target = buffer();
        return true;
    }
    void write(const std::string &fmt, ...) {
        bool res;
        va_list list;
        va_start(list, fmt);
        res = vwrite_socket(&_s, fmt.c_str(), list);
        va_end(list);
        assertC(res);
    }

    /* Data */
    void retrieveData(void) {
        assertC(retrieve_socket_data(&_s));
    }

private:
    socket_t _s;

    inline void assertC(bool good) const {
        if (!good)
            throw std::runtime_error("Socket exception");
    }
};