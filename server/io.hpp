#include <cstring>
#include <dirent.h>
#include <termios.h>

#define ESCAPE "\033"
#define ARROW_UP "\033[A"
#define ARROW_DOWN "\033[B"
#define ARROW_LEFT "\033[C"
#define ARROW_RIGHT "\033[D"

void getKey(char* s) {
	struct termios oldSettings, newSettings;
	tcgetattr(fileno(stdin), &oldSettings);
	newSettings = oldSettings;
	newSettings.c_lflag &= (~ICANON & ~ECHO);
	tcsetattr(fileno(stdin), TCSANOW, &newSettings);    
	
	fd_set set;
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 1000;
	FD_ZERO(&set);
	FD_SET(fileno(stdin), &set);
	
	//memset(s, '\0', sizeof(s));
	int res;
	char ch;
	do {
		res = select(fileno(stdin)+1, &set, NULL, NULL, &tv);
		if(res > 0) {
			read(fileno(stdin), &ch, 1);
			strcat(s, &ch);
		}
	} while(res > 0);
	tcsetattr(fileno(stdin), TCSANOW, &oldSettings);
}

void waitKey(char* key) {
	do {
		getKey(key);
	} while(key[0] == '\0');
}

void ls(const char* path) {
	DIR* dir = opendir(path);
	struct dirent* ent;
	if(dir != NULL) {
		while((ent = readdir(dir)) != NULL) {
			printf("%s ", ent->d_name);
		}
		printf("\n");
		closedir(dir);
	}
}
