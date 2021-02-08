#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#include "Protocol.hpp"


class Client {
	public:
	int fd;
	int port;
	struct sockaddr_in serverAddress;
	struct hostent* server;

	Client(char* hostname, int p) {
		port = p;
		fd = socket(AF_INET, SOCK_STREAM, 0); // fd < 0 = fail
		if(fd < 0)
			printf("failed opening socket\n");
		server = gethostbyname(hostname); // server == NULL = no such host
		if(server == NULL)
			printf("No such host\n");
		bzero((char*) &serverAddress, sizeof(serverAddress));
		serverAddress.sin_family = AF_INET;
		bcopy((char*) server->h_addr, (char*) &serverAddress.sin_addr.s_addr, server->h_length);
		serverAddress.sin_port = htons(port);
		if(connect(fd, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0)
			printf("couldn't connect to server\n");
	}

	~Client() {
		close(fd);
	}

	unsigned int createWindow() {
		char buffer[256];
		buffer[0] = (char) Request::WINDOW_CREATE;
		int n = write(fd, buffer, 1);
		n = read(fd, buffer, 255);
		unsigned int id;
		sscanf(buffer, "%d", &id);
		return id;
	}

	void setWindowAttributes(unsigned int id, unsigned int attrs) {
		char buffer[256];
		buffer[0] = (char) Request::WINDOW_SET_ATTRIBUTES;
		int n = write(fd, buffer, 1);
		snprintf(buffer, 255, "%d %d", id, attrs);
		n = write(fd, buffer, 255);
	}

	void resizeWindow(unsigned int id, int x, int y, int w, int h) {
		char buffer[256];
		buffer[0] = (char) Request::WINDOW_RESIZE;
		int n = write(fd, buffer, 1);
		snprintf(buffer, 255, "%d %d %d %d %d", id, x, y, w, h);
		n = write(fd, buffer, 255);
	}
};
