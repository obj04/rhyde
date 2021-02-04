#include "Server.hpp"


Server::Server(unsigned short p) {
	port = p;
	serverSocket = socket(AF_INET, SOCK_STREAM, 0); // serverSocket < 0 == fail
	bzero((char*) &serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(port);
	if(bind(serverSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0); // true = error
	listen(serverSocket, 5);
	dm = new DisplayManager();
	background(255);
}

Server::~Server() {
	close(serverSocket);
	close(clients[0].fd);
}

void Server::waitForClients() {
	unsigned int clientSocketLength = sizeof(clients[0].address);
	clients[0].fd = accept(serverSocket, (struct sockaddr*) &clients[0].address, &clientSocketLength); // clientSocket < 0 == fail
}

void Server::background(int alpha) {
	for(int y = 0; y < dm->fb->height; y++) {
		for(int x = 0; x < dm->fb->width; x++) {
			dm->layers[0]->setPixel(x, y, alpha << 24 | RGB(127, ((255 * x) / dm->fb->width), (255 - (255 * y) / dm->fb->height)));
		}
	}
}

void Server::processRequest() {
	char buffer[256];
	int n = read(clients[0].fd, buffer, 1); // n < 0 = error
	switch(buffer[0]) {
		case ClientRequest::CREATE_WINDOW:
			n = read(clients[0].fd, buffer, 255);
			int x, y, w, h;
			sscanf(buffer, "%d %d %d %d", &x, &y, &w, &h);
			printf("(%d|%d) %dx%d", x, y, w, h);
	}
//	n = write(clients[0].fd, "I got your message", 18); // n < 0 = error
}
