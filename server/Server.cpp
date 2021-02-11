#include "Server.hpp"


Server::Server(unsigned int p) {
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
	if(clients[0].fd < 0)
		printf("failed connecting\n");
}

void Server::background(int alpha) {
	for(int y = 0; y < dm->fb->height; y++) {
		for(int x = 0; x < dm->fb->width; x++) {
			dm->layers[0]->setPixel(y, x, alpha << 24 | RGB(127, ((255 * x) / dm->fb->width), (255 - (255 * y) / dm->fb->height)));
		}
	}
}

void Server::processRequest(unsigned int clientId) {
	char buffer[256];
	Socket client = clients[clientId];
	bzero(buffer, 256);
	int n = read(client.fd, buffer, 1);
	if(n < 0) // error
		return;
	unsigned int id, attrs, w, h;
	int x, y;
	Window* win;
	switch(buffer[0]) {
		case Request::WINDOW_CREATE:
			snprintf(buffer, 255, "%d", dm->createWindow());
			write(client.fd, buffer, 255);
			break;
		case Request::WINDOW_REPOSITION: 
			n = read(client.fd, buffer, 255);
			sscanf(buffer, "%d %d %d", &id, &x, &y);
			win = dm->getWindow(id);
			win->xPos = x;
			win->yPos = y;
			break;
		case Request::WINDOW_RESIZE: 
			n = read(client.fd, buffer, 255);
			sscanf(buffer, "%d %d %d", &id, &w, &h);
			win = dm->getWindow(id);
			win->resize(w, h);
			break;
		case Request::WINDOW_SET_ATTRIBUTES:
			n = read(client.fd, buffer, 255);
			sscanf(buffer, "%d %d", &id, &attrs);
			dm->getWindow(id)->flags = attrs;
			break;
		case Request::WINDOW_UPDATE:
			n = read(client.fd, buffer, 255);
			sscanf(buffer, "%d", &id);
			win = dm->getWindow(id);
			//dm->screen->lock->acquire();
			//win->lock->acquire();
			int arraylen = win->height * win->width * 4;
			n = 0;
			while(n < arraylen) {
				n += read(client.fd, &((char*) win->bitmap)[n], arraylen);
			}
			//dm->screen->lock->release();
			//win->lock->release();
			break;
	}
}