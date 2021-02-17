#pragma once

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

#include "../api/Protocol.hpp"
#include "../lib/Request.hpp"
#include "../lib/Thread.hpp"
#include "../lib/Graphics.hpp"
#include "../lib/MouseEvent.hpp"


class Window: public Canvas {
	public:
	char* title;
	unsigned int id;
	unsigned int flags;

	Window();
};

class Framebuffer {
	int fbfd = 0;
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	long screensize = 0;
	char* fbp = 0;
	
	public:
	unsigned int& width = vinfo.xres;
	unsigned int& height = vinfo.yres;
	unsigned int& bpp = vinfo.bits_per_pixel;
	int* bitmap;

	public:
	Framebuffer();
	~Framebuffer();
	void flush();
	void update();
};

class DisplayManager {
	Thread* autoRefresh;
	Thread* mouseListener;
	bool stopRequested = false;

	public:
	Canvas* screen;
	Window* layers[64];
	Canvas* mousePointer;
	Framebuffer* fb;

	DisplayManager();
	~DisplayManager();
	void refresh();
	void interrupt();
	bool interrupted();
	unsigned int createWindow();
	Window* getWindow(unsigned int id);
	void destroyWindow(unsigned int id);
};

class Server {
	public:
	typedef struct {
		int fd;
		struct sockaddr_in address;
	} Socket;
	unsigned int port;
	int serverSocket;
	struct sockaddr_in serverAddress;
	Socket clients[16];
	DisplayManager* dm;

	Server(unsigned int p);
	~Server();
	void waitForClients();
	void background(int alpha);
	void processRequest(unsigned int clientId);
};
