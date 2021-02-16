#include "Client.hpp"


Client::Client(char* hostname, int p) {
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

Client::~Client() {
	close(fd);
}
