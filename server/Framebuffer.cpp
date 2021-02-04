#include "RhyDE.hpp"


Framebuffer::Framebuffer() {
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
	
Framebuffer::~Framebuffer() {
	munmap(fbp, screensize);
	close(fbfd);
}

void Framebuffer::flush() {
	memset(buffer, 0, screensize);
}

void Framebuffer::update() {
	memcpy(fbp, buffer, screensize);
}
