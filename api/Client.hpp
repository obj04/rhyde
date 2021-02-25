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
#include "Conversation.hpp"
#include "../lib/Canvas.hpp"
#include "../lib/Thread.hpp"
#include "../lib/Queue.hpp"
#include "../lib/Request.hpp"
#include "../lib/ServerEvent.hpp"
#include "../lib/Clock.hpp"


class Client {
	public:
	int fd;
	int port;
	struct sockaddr_in serverAddress;
	struct hostent* server;
	void* callbackOwner;
	void (*eventCallback)(void*, ServerEvent*);
	Thread* loop;
	bool stopRequested = false;
	Queue* requestsPending = new Queue();

	Client(void (*evtCallback)(void*, ServerEvent*), void* owner, char* hostname, int p);
	~Client();
	Conversation* send(Request* r);
	void interrupt();
	bool interrupted();
};
