#include "Client.hpp"


int main() {
	Client* client = new Client("localhost", 38642);
	client->createWindow(10, 20, 30, 40);
	return 0;
}
