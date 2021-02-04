#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <unistd.h>
#include <linux/fb.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>

#include "dm/RhyDE.hpp"
#include "../api/Protocol.hpp"
#include "../lib/Thread.hpp"
#include "../lib/Graphics.hpp"
#include "../lib/MouseEvent.hpp"


class Framebuffer {
	int fbfd = 0;
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	long screensize = 0;
	char* fbp = 0;
	char* buffer;
	
	public:
	unsigned int& width = vinfo.xres;
	unsigned int& height = vinfo.yres;
	unsigned int& bpp = vinfo.bits_per_pixel;
	int** bitmap;

	public:
	Framebuffer();
	~Framebuffer();
	void flush();
	void update();
};

class DisplayManager {
	private:
	Thread* autoRefresh;
	Thread* mouseListener;
	bool stopRequested = false;

	public:
	Canvas* screen;
	LayeredCanvas* layers[64];
	Framebuffer* fb;

	DisplayManager();
	~DisplayManager();
	void refresh();
	void interrupt();
	bool interrupted();
};

class Server {
	public:
	typedef struct {
		int fd;
		struct sockaddr_in address;
	} Socket;
	unsigned short port;
	int serverSocket;
	struct sockaddr_in serverAddress;
	Socket clients[16];
	DisplayManager* dm;

	Server(unsigned short p);
	~Server();
	void waitForClients();
	void background(int alpha);
	void processRequest();
};

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
