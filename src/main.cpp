#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <unistd.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/mount.h>

#include "ui/UI.hpp"
#include "time.hpp"
#include "io.hpp"
#include "rhyde/RhyDE.hpp"
#include "rhyde/DisplayManager.hpp"
#include "ui/window/Window.hpp"


// square ☃
// fill █
// half ▒
// dot ·
// ┘┐┌└│─
DisplayManager* dm;
int width, height;

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
	printf("creating display manager. if this causes a segfault, adjust your screen resolution\n");
	dm = new DisplayManager();
	dm->layers[15]->line(0, 0, 0, 12, 0xff000000);
	dm->layers[15]->line(0, 0, 8, 8, 0xff000000);
	dm->layers[15]->line(8, 8, 0, 12, 0xff000000);
	dm->layers[15]->line(5, 10, 8, 16, 0xff000000);
	printf("done. creating fonts\n");
	PSFFont* font = loadFont(8, 16);
	PSFFont* windowTitleFont = loadFont(16, 32);
	width = dm->fb->width;
	height = dm->fb->height;
	printf("done. showing splash screen\n");

	background(dm, 255);
	dm->layers[1] = new WindowManager(1920, 1080);
	dm->layers[1]->layers[0] = new Window("test window", windowTitleFont);
	end();
	return 0;
}
