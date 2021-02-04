run: build
	sudo ./server.out &
	sudo ./api.out

build:
	./build.sh server
	sleep 1
	./build.sh api
