CXX = g++
PREFIX = /usr
PACKAGES = clanApp-2.3 clanCore-2.3 clanDatabase-2.3 clanDisplay-2.3 clanGL-2.3 clanNetwork-2.3 clanSound-2.3 clanSqlite-2.3 clanVorbis-2.3 lua
CXXFLAGS = -DGAME_DATA_DIR=\"$(PREFIX)/share/bmgui\" $(shell pkg-config --cflags $(PACKAGES)) -Wall
LIBS = $(shell pkg-config --libs $(PACKAGES)) -ltolua++-5.1
BIN = bmgui

PCH = src/Precompiled.h.gch
OBJ = \
	src/Application.o \
	src/Balance.o \
	src/Database.o \
	src/Font.o \
	src/FontResource.o \
	src/Graphics.o \
	src/Keyboard.o \
	src/LuaBindings.o \
	src/LuaModule.o \
	src/LuaScript.o \
	src/Mouse.o \
	src/Precompiled.o \
	src/Profile.o \
	src/Program.o \
	src/ResourceManager.o \
	src/ResourceQueue.o \
	src/Sound.o \
	src/SoundResource.o \
	src/Sprite.o \
	src/SpriteResource.o

release : CXXFLAGS += -O2 -s
release : $(BIN)

debug : CXXFLAGS += -g -O0
debug : $(BIN)

$(BIN) : $(PCH) $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(BIN) $(LIBS)

%.gch : %
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

install:
	install $(BIN) $(PREFIX)/bin
	install bmgui_start $(PREFIX)/bin
	mkdir -p $(PREFIX)/share/bmgui
	cp -rf data/* $(PREFIX)/share/bmgui
	install files/bmgui_update $(PREFIX)/bin
	cp -f files/bmgui.png $(PREFIX)/share/pixmaps
	cp -f files/bmgui.desktop /home/bm/Desktop
	cp -f files/bminfo /etc
	chown bm:bm /home/bm/Desktop/bmgui.desktop
	install files/bmgui_xinput_calibrator $(PREFIX)/bin/bmgui_xinput_calibrator
	chmod +x $(PREFIX)/bin/bmgui_xinput_calibrator

uninstall:
	rm -f $(PREFIX)/bin/$(BIN)
	rm -f $(PREFIX)/bin/bmgui_update
	rm -f $(PREFIX)/bin/bmgui_start
	rm -rf $(PREFIX)/share/bmgui
	rm -f $(PREFIX)/share/pixmaps/bmgui.png
	rm -f /home/bm/Desktop/bmgui.desktop
	rm -f /etc/bminfo
	rm -f $(PREFIX)/bin/bmgui_xinput_calibrator

clean cleandebug cleanrelease:
	rm -f $(PCH) $(OBJ) $(BIN)
