.PHONY: run build server api

run: build
	sudo ./server.out

build: server api

server:
	./build.sh server

api:
	./build.sh api
