#include "Client.hpp"


Client::Client(void (*evtCallback)(void*, ServerEvent*), void* owner, char* hostname, int p) {
	callbackOwner = owner;
	eventCallback = evtCallback;
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
	printf("connecting\n");
	if(connect(fd, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0)
		printf("couldn't connect to server\n");
	printf("connected\n");

	loop = new Thread([](void* args) -> void* {
		Client* client = (Client*) args;
		while(!(client->interrupted() && client->requestsPending->isEmpty())) {
			if(client->requestsPending->isEmpty()) {
				Request* request = new Request();
				request->addObject(Command::POLL_EVENT);
				request->send(client->fd);
				Request* answer = new Request(client->fd);
				if(answer->elementsCount > 0) {
					//ServerEvent* e = (ServerEvent*) answer->getObject(0).object;
					client->eventCallback(client->callbackOwner, new ServerEvent(answer));
				}
				usleep(10000);
			} else {
				Conversation* conv = (Conversation*) client->requestsPending->pop();
				conv->request->send(client->fd);
				conv->answer = new Request(client->fd);
				conv->lock->release();
			}
		}
	}, (void*) this);
	loop->start();
}

Client::~Client() {
	interrupt();
	loop->join();
	close(fd);
}

void Client::interrupt() {
	stopRequested = true;
}

bool Client::interrupted() {
	return stopRequested;
}
