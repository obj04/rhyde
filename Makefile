default: run


build:
	cd src && g++ -m32 -march=i686 -I. -static -ffreestanding -pthread main.cpp -o ../rhyde
	chmod +x rhyde

run: build
	sudo ./rhyde