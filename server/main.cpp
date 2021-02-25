#include "Server.hpp"
#include "io.hpp"


bool escape() {
	char junk[4];
	memset(junk, '\0', sizeof(junk));
	waitKey(junk);
	if(strcmp(junk, ESCAPE))
		return true;
	return false;
}

int main(int argc, char *argv[]) {
	Server* server = new Server(38642);
	//popen("./api.out", "r");
	server->waitForClients();
	while(true) {//!escape()) {
		server->processRequest(0);
		//usleep(100000);
	}
	return 0;
}
