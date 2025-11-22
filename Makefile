app = bin/beatmatcher 
test_app = bin/test

build_dir = build/
includeDir = include/
main = src/main.cpp
test = src/test.cpp
objects = build/laserbeam.o build/animator.o build/config.o build/debug.o build/music.o build/spot.o build/addr_LED.o build/redrayz.o build/DMXio.o #build/spider.o 
qlc_files = QLC/fixtures/AddrLED_CtrlPanel.qxf QLC/fixtures/RedRayz_CtrlPanel.qxf QLC/fixtures/SpotRack_CtrlPanel.qxf QLC/fixtures/Beatmatcher-Control-Panel.qxf  QLC/fixtures/BaseFixture_CtrlPanel.qxf QLC/Config_beatmatcher_controler.qxw
qlc_dest_files = 
qlc_fix_path = /home/reepier/.qlcplus/fixtures
qlc_bkp_dirname = bkp_$(shell date "+%Y_%m_%d@%T")

libs = -lola -lolacommon -lcurses  -lfftw3 -lwiringPi -lprotobuf -lrtaudio 
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
	rm QLC/Functions

build/:
	mkdir build
build/animator.o: src/animator.cpp include/animator.h $(genericInclude) 
	g++ $(flags) -c src/animator.cpp $(includePaths) -o build/animator.o
build/config.o: src/config.cpp $(genericInclude)
	g++ $(flags) -c src/config.cpp $(includePaths) -o build/config.o
build/debug.o: src/debug.cpp include/debug.h $(genericInclude)
	g++ $(flags) -c src/debug.cpp $(includePaths) -o build/debug.o -lcurses
build/music.o: src/music.cpp include/music.h $(genericInclude)
	g++ $(flags) -c src/music.cpp $(includePaths) -o build/music.o
#build/spider.o: src/spider.cpp include/spider.h $(genericInclude)
#	g++ $(flags) -c src/spider.cpp $(includePaths) -o build/spider.o
build/spot.o: src/spot.cpp include/spot.h $(genericInclude)
	g++ $(flags) -c src/spot.cpp $(includePaths) -o build/spot.o
build/addr_LED.o: src/addr_LED.cpp include/addr_LED.h $(genericInclude)
	g++ $(flags) -c src/addr_LED.cpp $(includePaths) -o build/addr_LED.o
build/redrayz.o: src/redrayz.cpp include/redrayz.h $(genericInclude)
	g++ $(flags) -c src/redrayz.cpp $(includePaths) -o build/redrayz.o
build/DMXio.o: src/DMXio.cpp include/DMXio.h include/addr_LED.h $(genericInclude)
	g++ $(flags) -c src/DMXio.cpp $(includePaths) -o build/DMXio.o
build/laserbeam.o: src/laserbeam.cpp include/laserbeam.h $(genericInclude)
	g++ $(flags) -c src/laserbeam.cpp $(includePaths) -o build/laserbeam.o

install_qlc: $(qlc_files)
#Backup
	mkdir /home/reepier/Documents/QLC/$(qlc_bkp_dirname)
	cp /home/reepier/Documents/QLC/*.qxw /home/reepier/Documents/QLC/$(qlc_bkp_dirname)
	mkdir $(qlc_fix_path)/$(qlc_bkp_dirname)
	cp $(qlc_fix_path)/*.qxf $(qlc_fix_path)/$(qlc_bkp_dirname)
#Install
	cp QLC/Config_beatmatcher_controler.qxw /home/reepier/Documents/QLC/
	cp QLC/fixtures/BaseFixture_CtrlPanel.qxf 		$(qlc_fix_path)
	cp QLC/fixtures/AddrLED_CtrlPanel.qxf 	$(qlc_fix_path)
	cp QLC/fixtures/RedRayz_CtrlPanel.qxf 			$(qlc_fix_path)
	cp QLC/fixtures/SpotRack_CtrlPanel.qxf 			$(qlc_fix_path)
	cp QLC/fixtures/Beatmatcher-Control-Panel.qxf 	$(qlc_fix_path)
	cp QLC/fixtures/Beam_CtrlPanel.qxf				$(qlc_fix_path)

get_qlc: 
	cp /home/reepier/Documents/QLC/Config_beatmatcher_controler.qxw QLC/
	cp $(qlc_fix_path)/BaseFixture_CtrlPanel.qxf		QLC/fixtures	
	cp $(qlc_fix_path)/AddrLED_CtrlPanel.qxf			QLC/fixtures	
	cp $(qlc_fix_path)/RedRayz_CtrlPanel.qxf			QLC/fixtures
	cp $(qlc_fix_path)/SpotRack_CtrlPanel.qxf			QLC/fixtures
	cp $(qlc_fix_path)/Beatmatcher-Control-Panel.qxf    QLC/fixtures
	cp $(qlc_fix_path)/Beam_CtrlPanel.qxf				QLC/fixtures

clean:
	rm -f build/*.o bin/* *.log */*.log QLC/*


debug:
	echo $(qlc_bkp_dirname)