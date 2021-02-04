#include "Server.hpp"


int main(int argc, char *argv[]) {
	Server* server = new Server(38642);
	server->waitForClients();
	server->processRequest();
	return 0;
}
