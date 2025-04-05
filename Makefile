app = bin/beatmatcher 
test_app = bin/test

build_dir = build/
includeDir = include/
main = src/main.cpp
test = src/test.cpp
objects = build/MCP3008.o build/animator.o build/config.o build/debug.o build/laser.o build/music.o build/spider.o build/spot.o build/addr_LED.o build/redrayz.o build/DMXio.o
libs = -lola -lolacommon -lcurses  -lfftw3 -lwiringPi -lprotobuf -lrtaudio #-lgpio -lPCA9685 
flags = -w -g -std=c++20
includePaths = -I. -I.. -Iinclude
genericInclude = include/config.h include/sysfcn.h include/commonTypes.h include/debug.h

app: $(app)

test: $(test_app)

all: $(test_app) $(app)

$(test_app) : $(test) $(build_dir) $(objects)
	g++ $(flags) src/test.cpp $(objects) $(includePaths) $(libs) -o $(test_app)

$(app): $(main) $(build_dir) $(objects) 
	g++ $(flags) src/main.cpp $(objects) $(includePaths) $(libs) -o $(app)

build/:
	mkdir build
build/animator.o: src/animator.cpp include/animator.h $(genericInclude) 
	g++ $(flags) -c src/animator.cpp $(includePaths) -o build/animator.o
build/config.o: src/config.cpp $(genericInclude)
	g++ $(flags) -c src/config.cpp $(includePaths) -o build/config.o
build/debug.o: src/debug.cpp include/debug.h $(genericInclude)
	g++ $(flags) -c src/debug.cpp $(includePaths) -o build/debug.o -lcurses
build/laser.o: src/laser.cpp include/laser.h $(genericInclude)
	g++ $(flags) -c src/laser.cpp $(includePaths) -o build/laser.o
build/music.o: src/music.cpp include/music.h $(genericInclude)
	g++ $(flags) -c src/music.cpp $(includePaths) -o build/music.o
build/spider.o: src/spider.cpp include/spider.h $(genericInclude)
	g++ $(flags) -c src/spider.cpp $(includePaths) -o build/spider.o
build/spot.o: src/spot.cpp include/spot.h $(genericInclude)
	g++ $(flags) -c src/spot.cpp $(includePaths) -o build/spot.o
build/MCP3008.o: src/MCP3008.cpp
	g++ $(flags) -c src/MCP3008.cpp $(includePaths) -o build/MCP3008.o
build/addr_LED.o: src/addr_LED.cpp include/addr_LED.h $(genericInclude)
	g++ $(flags) -c src/addr_LED.cpp $(includePaths) -o build/addr_LED.o
build/redrayz.o: src/redrayz.cpp include/redrayz.h $(genericInclude)
	g++ $(flags) -c src/redrayz.cpp $(includePaths) -o build/redrayz.o
build/DMXio.o: src/DMXio.cpp include/DMXio.h include/addr_LED.h $(genericInclude)
	g++ $(flags) -c src/DMXio.cpp $(includePaths) -o build/DMXio.o

clean:
	rm build/*.o bin/* .*/*.log *.log
	
