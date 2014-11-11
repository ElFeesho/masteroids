OBJS=fixeddirectionmover.o direction.o shape.o position.o gamescreen.o menuscreen.o entitylist.o screenmanager.o gamepadinputmanager.o main.o UFO.o about.o asteroid.o bullet.o controlconf.o debrisfragment.o engine.o gameover.o ingame.o menu.o options.o ship.o ufobullet.o libwiiwrap/ogcsys.o libwiiwrap/gccore.o libwiiwrap/ogc/lwp_watchdog.o libwiiwrap/wiiuse/wpad.o sdlgfx.o keyboardsource.o
LIBS=`sdl-config --libs` -lm -lSDL_gfx
CC=g++
CFLAGS=`sdl-config --cflags` -Ilibwiiwrap -Wfatal-errors -g
CXXFLAGS=`sdl-config --cflags` -Ilibwiiwrap -Wfatal-errors -g -std=c++11
PROG=masteroids

all:$(OBJS)
	g++ -o $(PROG) $(OBJS) $(LIBS)

%o:%cpp
	g++ $(CXXFLAGS) $< -c

clean:
	rm -f $(PROG) $(OBJS)
