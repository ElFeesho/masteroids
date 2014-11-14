OBJS=elapsedtimetolive.o \
renderers/optionsrenderer.o \
renderers/shiprenderer.o \
alivemonitor.o \
time.o debris.o \
debrisfountain.o \
movers/fixeddirectionmover.o \
direction.o \
shape.o \
position.o \
gamescreen.o \
menuscreen.o \
entitylist.o \
screenmanager.o \
input/gamepadinputmanager.o \
main.o \
UFO.o \
about.o \
asteroid.o \
bullet.o \
controlconf.o \
gameover.o \
ingame.o \
menu.o \
options.o \
ship.o \
ufobullet.o \
libwiiwrap/ogcsys.o \
libwiiwrap/gccore.o \
libwiiwrap/ogc/lwp_watchdog.o \
libwiiwrap/wiiuse/wpad.o \
gfx/sdlgfx.o \
input/keyboardsource.o

LIBS=`sdl-config --libs` -lm -lSDL_gfx
CC=g++
CFLAGS=`sdl-config --cflags` -Ilibwiiwrap -Wfatal-errors -g -I.
CXXFLAGS=`sdl-config --cflags` -Ilibwiiwrap -Wfatal-errors -g -std=c++11 -I.
PROG=masteroids

all:$(OBJS)
	g++ -o $(PROG) $(OBJS) $(LIBS)

%o:%cpp
	g++ $(CXXFLAGS) $< -c

clean:
	rm -f $(PROG) $(OBJS)
