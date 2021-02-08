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

PSFFont* loadFont(int width, int height) {
	char fontFile[16];
	snprintf(fontFile, 16, "%dx%d.psfu", width, height);
	struct stat fileStats;
	
	stat(fontFile, &fileStats);
	int fileSize = fileStats.st_size;
	unsigned char* psfData = new unsigned char[fileSize];
	FILE* psf = fopen(fontFile, "r");
	fread(psfData, fileSize, fileSize, psf);
	fclose(psf);
	return new PSFFont(psfData);
}

int main(int argc, char *argv[]) {
	Server* server = new Server(38642);
	popen("./api.out", "r");
	server->waitForClients();
	while(true) {//!escape()) {
		server->processRequest(0);
		usleep(100000);
	}
	return 0;
}
