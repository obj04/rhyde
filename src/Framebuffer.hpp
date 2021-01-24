#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <unistd.h>
#include <linux/fb.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

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
	Framebuffer() {
		fbfd = open("/dev/fb0", O_RDWR);
		if(fbfd == -1) {
			printf("cannot open framebuffer\n");
			return;
		}
		printf("Opened framebuffer.\n");
		if(ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) return;
		if(ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) return;
		width = finfo.line_length / 4;
		height = finfo.smem_len / finfo.line_length;
		if(ioctl(fbfd, FBIOPUT_VSCREENINFO, &vinfo) == -1) return;

		screensize = width * height * bpp / 8;
		printf("%dx%d %dbits, screensize: %d, line length: %d\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel, screensize, finfo.line_length);
		
		fbp = (char*) mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
		if((long) fbp == -1) return;
		printf("The framebuffer device was mapped successfully.\n");
		
		buffer = new char[screensize];
		bitmap = new int*[height];
		for(int i = 0; i < height; i++)
			bitmap[i] = (int*) (&buffer[((unsigned long long) i * screensize) / (unsigned long long) height]);
	}
	
	~Framebuffer() {
		munmap(fbp, screensize);
		close(fbfd);
	}

	void flush() {
		memset(buffer, 0, screensize);
	}

	void update() {
		memcpy(fbp, buffer, screensize);
	}
};
