FLAGS = -Wall -Wextra -std=c++20

all: build/program

build/program: build/main.o build/directory-watcher.o build/logger.o
	g++ -o build/program build/main.o build/directory-watcher.o build/logger.o

build/main.o: src/main.cpp src/directory-watcher.h
	g++ -o build/main.o -c src/main.cpp $(FLAGS)

build/directory-watcher.o: src/directory-watcher.cpp src/directory-watcher.h
	g++ -o build/directory-watcher.o -c src/directory-watcher.cpp $(FLAGS)

build/logger.o: src/logger.cpp src/logger.h
	g++ -o build/logger.o -c src/logger.cpp $(FLAGS)

clean:
	rm -rf build/
