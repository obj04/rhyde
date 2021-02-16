#pragma once

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#include "Protocol.hpp"
#include "../lib/Graphics.hpp"
#include "../lib/Clock.hpp"


class Client {
	public:
	int fd;
	int port;
	struct sockaddr_in serverAddress;
	struct hostent* server;

	Client(char* hostname, int p);
	~Client();
};
