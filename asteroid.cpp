#include "asteroid.h"
#include "options.h"
#include <cstdlib>
#include <cmath>

#include "time.h"

#include "movers/fixeddirectionmover.h"

static inline double createSpeed()
{
	double speed = 1+(rand() % (Options::difficulty+1));
	if(rand()%2 == 1)
	{
		speed *= -1;
	}
	return speed;
}

Asteroid::Asteroid() : mover(new FixedDirectionMover()), astroRenderer(AsteroidRenderer()), rot_speed(rand()%10-5), travelDirection(Direction(createSpeed(), rand() % 360))
{
	position().Rotation(rand()%360);
	shape().Radius(25.0f);

	int pos = rand()%4;
	switch(pos)
	{
		case 0: // Top row
			position().X(rand()%160*4);
			position().Y(-25.0f);
			break;
		case 1: // Bottom row
			position().X(rand()%160*4);
			position().Y(480+25.0f);
			break;
		case 2: // Left column
			position().Y(rand()%120*4);
			position().X(-25.0f);
			break;
		case 3: // Right column
			position().Y(rand()%120*4);
			position().X(640+25.0f);
			break;
	}

	
}

Asteroid::Asteroid(double scale, const Position &nposition) : mover(new FixedDirectionMover()), astroRenderer(AsteroidRenderer()), rot_speed(rand()%10-5), pos(nposition), travelDirection(Direction(createSpeed(), rand() % 360))
{
	position().Rotation(rand()%360);
	shape().Radius(scale);

}

Asteroid::~Asteroid()
{
	delete mover;
}

bool Asteroid::update()
{
	position().rotate(Time::factorTime(rot_speed));
	mover->move(direction(), position(), shape());
	return aliveMonitor().alive();
}

void Asteroid::render(GfxWrapper* gfx)
{
	renderer().render(gfx, position(), shape(), direction());
}

