#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <unistd.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <sys/mount.h>
#include "time.hpp"
#include "io.hpp"
#include "DisplayManager.hpp"


// square ☃
// fill █
// half ▒
// dot ·
// ┘┐┌└│─
DisplayManager* dm;
int width, height;
PSFFont* font;
PSFFont* largeFont;



void background(DisplayManager* dm, int alpha) {
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			dm->layers[0]->bitmap[y][x] = alpha << 24 | RGB(127, ((255 * x) / width), (255 - (255 * y) / height));
		}
	}
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

void end() {
	while(true) {
		char key[8];
		waitKey(key);
		if(strcmp(key, ESCAPE) == 0)
			return;
	}
}

int main(int argc, char *argv[]) {
	//system("mknod /dev/input/mice c 13 63");

	printf("creating display manager. if this causes a segfault, adjust your screen resolution\n");
	dm = new DisplayManager();
	dm->layers[15]->line(0, 0, 0, 12, 0xff000000);
	dm->layers[15]->line(0, 0, 8, 8, 0xff000000);
	dm->layers[15]->line(8, 8, 0, 12, 0xff000000);
	dm->layers[15]->line(5, 10, 8, 16, 0xff000000);
	printf("done. creating fonts\n");
	font = loadFont(8, 16);
	largeFont = loadFont(16, 32);
	width = dm->fb->width;
	height = dm->fb->height;
	printf("done. showing splash screen\n");

	background(dm, 255);
	dm->layers[2] = new NestableCanvas(600, 400);
	dm->layers[2]->xPos = (width - dm->layers[2]->width) / 2;
	dm->layers[2]->yPos = (height - dm->layers[2]->height) / 2;
	for(int i = 0; i < 1000; i++) {
		dm->layers[2]->roundRect(300 - (i * 300 / 1000), 200 - (i * 200 / 1000),
														 300 + (i * 300 / 1000), 200 + (i * 200 / 1000),
														 (200 - (190 * i / 1000)) * i / 1000, 0x80ffffff);
		usleep(1000);
	}

	dm->layers[3] = new NestableCanvas(600, 400);
	dm->layers[3]->xPos = (width - dm->layers[3]->width) / 2;
	dm->layers[3]->yPos = (height - dm->layers[3]->height) / 2;
	dm->layers[3]->text(8, 8, largeFont, "some kind of test window", 0xff000000);
	dm->layers[3]->text(8, 72, font, "(This is just a rounded rectangle)", 0xff000000);

	end();
	return 0;

	while(true) {
		char key[8];
		waitKey(key);
		if(strcmp(key, ARROW_UP) == 0)
			printf("\033[Aup\n");
		//sleep(10);
	}

	return 0;
	end();
}
