FLAGS = -Wall -Wextra -std=c++20

all: program

program: src/main.o src/directory-watcher.o src/logger.o
	g++ -o program src/main.o src/directory-watcher.o src/logger.o

src/main.o: src/main.cpp src/directory-watcher.h
	g++ -o src/main.o -c src/main.cpp $(FLAGS)

src/directory-watcher.o: src/directory-watcher.cpp src/directory-watcher.h
	g++ -o src/directory-watcher.o -c src/directory-watcher.cpp $(FLAGS)

src/logger.o: src/logger.cpp src/logger.h
	g++ -o src/logger.o -c src/logger.cpp $(FLAGS)

clean:
	rm -rf *.o *~ program
