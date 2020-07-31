all: compile

compile:
	@echo "Compiling..."
	@test -d ./bin || mkdir bin
	@g++ -I./ -o bin/server ./server/server.cpp -O0 -lgmp
	@g++ -I./ -o bin/client ./client/client.cpp -O0 -lgmp
	@clear
	@bin/server

clean:
	@echo "Cleaning up..."
	@rm -R ./bin