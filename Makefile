app = bin/beatmatcher 
test_app = bin/test

objects = build/MCP3008.o build/animator.o build/config.o build/debug.o build/laser.o build/LED.o build/music.o build/spider.o build/spot.o
libs = -lola -lolacommon -lcurses -lwiringPi -lfftw3 -llgpio -lPCA9685

all: $(test_app) $(app)

$(test_app) : $(objects)
	g++ src/test.cpp $(objects) -Iinclude $(libs) -o $(test_app)

$(app): $(objects)
	g++ src/main.cpp $(objects) -Iinclude $(libs) -o $(app)


build/animator.o: src/animator.cpp
	g++ -c src/animator.cpp -I include -o build/animator.o
build/config.o: src/config.cpp
	g++ -c src/config.cpp -I include -o build/config.o
build/debug.o: src/debug.cpp
	g++ -c src/debug.cpp -I include -o build/debug.o -lcurses
build/laser.o: src/laser.cpp
	g++ -c src/laser.cpp -I include -o build/laser.o
build/LED.o: src/LED.cpp
	g++ -c src/LED.cpp -I include -o build/LED.o
build/music.o: src/music.cpp
	g++ -c src/music.cpp -I include -o build/music.o
build/spider.o: src/spider.cpp
	g++ -c src/spider.cpp -I include -o build/spider.o
build/spot.o: src/spot.cpp
	g++ -c src/spot.cpp -I include -o build/spot.o
build/MCP3008.o: src/MCP3008.cpp
	g++ -c src/MCP3008.cpp -I include -o build/MCP3008.o