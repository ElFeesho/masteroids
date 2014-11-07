OBJS=gamepadinputmanager.o main.o UFO.o about.o asteroid.o bullet.o collobj.o controlconf.o debris.o engine.o entity.o gameover.o ingame.o menu.o options.o ship.o ufobullet.o libwiiwrap/ogcsys.o libwiiwrap/gccore.o libwiiwrap/ogc/lwp_watchdog.o libwiiwrap/wiiuse/wpad.o sdlgfx.o keyboardsource.o
LIBS=`sdl-config --libs` -lm -lSDL_gfx
CC=g++
CFLAGS=`sdl-config --cflags` -Ilibwiiwrap -Wfatal-errors -g
CXXFLAGS=`sdl-config --cflags` -Ilibwiiwrap -Wfatal-errors -g
PROG=masteroids

all:$(OBJS)
	g++ -o $(PROG) $(OBJS) $(LIBS)

%o:%cpp
	g++ $(CXXFLAGS) $< -c

clean:
	rm -f $(PROG) $(OBJS)
