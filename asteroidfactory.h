#ifndef __ASTEROID_FACTORY_H__
#define __ASTEROID_FACTORY_H__

#include "renderers/asteroidrenderer.h"
#include "movers/fixeddirectionmover.h"
#include "actor.h"

static double random(double min, double max)
{
    int randNum = rand()%10000;
    max -= min;
    return (min + ((double)randNum/10000.0)*max) * (rand()%100 > 50 ? -1 : 1);
}

class AsteroidFactory
{
public:

    static void randomiseAsteroid(Entity *asteroid)
    {
        asteroid->direction().Angle(random(0.0, M_PI*2.0f));
        asteroid->direction().Speed(random(0.5, 2.0f));
        asteroid->direction().Spin(random(0.5, 2.0f));
    }

    static Entity *createAsteroid(double radius)
    {
        Actor *asteroid = new Actor(new AsteroidRenderer(), new FixedDirectionMover(), AlwaysAlive::alwaysAlive);
        randomiseAsteroid(asteroid);
        asteroid->shape().Radius(radius);
        asteroid->position().X(-radius);
        asteroid->position().Y(-radius);
        return asteroid;
    }

    static Entity *createAsteroid(double radius, Position position)
    {
        Actor *asteroid = new Actor(new AsteroidRenderer(), new FixedDirectionMover(), AlwaysAlive::alwaysAlive);
        randomiseAsteroid(asteroid);
        asteroid->shape().Radius(radius);
        asteroid->position().X(position.X());
        asteroid->position().Y(position.Y());
        return asteroid;
    }

};

#endif