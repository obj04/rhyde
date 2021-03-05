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
	printf("waiting for clients\n");
	unsigned int clientSocketLength = sizeof(clients[0].address);
	clients[0].fd = accept(serverSocket, (struct sockaddr*) &clients[0].address, &clientSocketLength); // clientSocket < 0 == fail
	if(clients[0].fd < 0)
		printf("failed connecting\n");
	printf("client connected\n");
}

void Server::background(int alpha) {
	for(int y = 0; y < dm->fb->height; y++) {
		for(int x = 0; x < dm->fb->width; x++) {
			dm->layers[0]->setPixel(y, x, alpha << 24 | RGB(127, ((255 * x) / dm->fb->width), (255 - (255 * y) / dm->fb->height)));
		}
	}
}

void Server::processRequest(unsigned int clientId) {
	Socket client = clients[clientId];
	Request* request = new Request(client.fd);
	int cmd = request->getIntValue(0);
	//if(cmd != Command::POLL_EVENT)
	//	printf("got cmd %d\n", cmd);
	Request* answer = new Request();
	unsigned int id, arraylen, attrs, w, h;
	int x, y;
	Window* win;
	switch(cmd) {
		case Command::POLL_EVENT:
			if(!dm->eventQueue->isEmpty()) {
				ServerEvent* e = (ServerEvent*) dm->eventQueue->pop();
				answer->addObject(e, sizeof(ServerEvent));
			}
			break;
		case Command::WINDOW_CREATE:
			printf("create window\n");
			id = dm->createWindow();
			answer->addObject(id);
			break;
		case Command::WINDOW_REPOSITION: 
			id = request->getIntValue(1);
			x = request->getIntValue(2);
			y = request->getIntValue(3);
			win = dm->getWindow(id);
			win->xPos = x;
			win->yPos = y;
			answer->addObject(Command::ACK);
			break;
		case Command::WINDOW_RESIZE: 
			id = request->getIntValue(1);
			w = request->getIntValue(2);
			h = request->getIntValue(3);
			win = dm->getWindow(id);
			win->resize(w, h);
			answer->addObject(Command::ACK);
			break;
		case Command::WINDOW_SET_ATTRIBUTES:
			id = request->getIntValue(1);
			attrs = request->getIntValue(2);
			win = dm->getWindow(id);
			win->flags = attrs;
			answer->addObject(Command::ACK);
			break;
		case Command::CLIENT_AREA_UPDATE:
			id = request->getIntValue(1);
			x = request->getIntValue(2);
			y = request->getIntValue(3);
			w = request->getIntValue(4);
			h = request->getIntValue(5);
			win = dm->getWindow(id);
			arraylen = w * h * 4;
			win->assimilate(x, y, w, h, (int*) request->getObject(6).object);
			answer->addObject(Command::ACK);
			break;
		default:
			printf("unknown opcode: %d\n", cmd);
			answer->addObject(Command::ACK);
	}
	answer->send(client.fd);
}
