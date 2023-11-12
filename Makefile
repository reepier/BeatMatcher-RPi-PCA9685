app = bin/beatmatcher 
test_app = bin/test

build_dir = build/
main = src/main.cpp
test = src/test.cpp
objects = build/MCP3008.o build/animator.o build/config.o build/debug.o build/laser.o build/LED.o build/music.o build/spider.o build/spot.o
libs = -lola -lolacommon -lcurses  -lfftw3 -lwiringPi -llgpio -lPCA9685 

app: $(app)

test: $(test_app)

all: $(test_app) $(app)

$(test_app) : $(test) $(build_dir) $(objects)
	g++ src/test.cpp $(objects) -Iinclude $(libs) -o $(test_app)

$(app): $(main) $(build_dir) $(objects) 
	g++ src/main.cpp $(objects) -Iinclude $(libs) -o $(app)

build/:
	mkdir build
build/animator.o: src/animator.cpp include/animator.h 
	g++ -c src/animator.cpp -I include -o build/animator.o
build/config.o: src/config.cpp include/config.h
	g++ -c src/config.cpp -I include -o build/config.o
build/debug.o: src/debug.cpp include/debug.h
	g++ -c src/debug.cpp -I include -o build/debug.o -lcurses
build/laser.o: src/laser.cpp include/laser.h
	g++ -c src/laser.cpp -I include -o build/laser.o
build/LED.o: src/LED.cpp include/LED.h
	g++ -c src/LED.cpp -I include -o build/LED.o
build/music.o: src/music.cpp include/music.h
	g++ -c src/music.cpp -I include -o build/music.o
build/spider.o: src/spider.cpp include/spider.h
	g++ -c src/spider.cpp -I include -o build/spider.o
build/spot.o: src/spot.cpp include/spot.h
	g++ -c src/spot.cpp -I include -o build/spot.o
build/MCP3008.o: src/MCP3008.cpp
	g++ -c src/MCP3008.cpp -I include -o build/MCP3008.o


clean:
	rm build/*.o bin/*
	