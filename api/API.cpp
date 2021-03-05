#include "API.hpp"
#include "ui/Component.hpp"
#include <sys/stat.h>


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
//
//-----------------------------
//
API::API() {
	eventListener = [](void* ptr, ServerEvent e) -> void {
		API* api = (API*) ptr;
		for(void* c : api->components->items) {
			Component* comp = (Component*) c;
			if(comp != NULL) {
				if(comp->contains(e.mouse.xPos, e.mouse.yPos)) {
					e.mouse.xPos -= comp->xPos;
					e.mouse.yPos -= comp->yPos;
					comp->handleEvent(e);
				}
			}
		}
	};
	defaultFont = loadFont(8, 16);
}

API::~API() {
	delete client;
}

void API::connect(char* host, int port) {
	client = new Client(eventListener, this, host, port);
}

Conversation* API::send(Request* r) {
	Conversation* conv = new Conversation(r);
	conv->lock->acquire();
	client->requestsPending->push(conv);
	return conv;
}

void API::updateClientArea(void* ptr) {
	Component* comp = (Component*) ptr;
	Component* window;
	for(void* c : components->items) {
		window = (Component*) c;
		if(window->id == comp->id) {
			window->render();
			break;
		}
	}
	Point pos = comp->getAbsolutePosition();
	pos.move(- comp->xPos, - comp->yPos);
	Canvas area = Canvas(comp->width, comp->height);
	area.assimilate(pos.x, pos.y, area.width, area.height, window->bitmap);

	Request* request = new Request();
	request->addObject(Command::CLIENT_AREA_UPDATE);
	request->addObject(comp->id);
	request->addObject(pos.x);
	request->addObject(pos.y);
	request->addObject(area.width);
	request->addObject(area.height);
	request->addObject(area.bitmap, area.width * area.height * 4);
	send(request);
}
