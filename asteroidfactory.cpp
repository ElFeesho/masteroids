//
// Created by Christopher Sawczuk on 27/07/2015.
//

#include <iostream>
#include "asteroidfactory.h"


static inline double randomAngle();

static inline double randomSpeed();

static inline double randomSpin();


AsteroidFactory::AsteroidFactory() : renderers{AsteroidRenderer(), AsteroidRenderer(), AsteroidRenderer(), AsteroidRenderer(), AsteroidRenderer()},
                                     mover(FixedDirectionMover()) {

    std::cout << "AsteroidFactory" << std::endl;
}

Actor *AsteroidFactory::createAsteroid(double radius, Position pos) {
    Actor *asteroid = new Actor(RGB::WHITE, mover, renderers[rand() % 5], std::unique_ptr<AlwaysAlive>(new AlwaysAlive()));
    asteroid->shape().Radius(radius);
    asteroid->direction().Angle(randomAngle());
    asteroid->direction().Speed(randomSpeed());
    asteroid->direction().Spin(randomSpin());
    asteroid->position().X(pos.X());
    asteroid->position().Y(pos.Y());
    asteroid->position().Rotation(pos.Rotation());
    return asteroid;
}

double static inline randomAngle() {
    double factor = rand() / (double) RAND_MAX;
    return (M_PI * 2.0f) * factor;
}

double static inline randomSpeed() {
    double factor = rand() / (double) RAND_MAX;
    double speed = 3.0f * factor;
    return speed + 0.5f;
}

double static inline randomSpin() {
    double factor = rand() / (double) RAND_MAX;
    double speed = 0.05f + (0.1f * factor);

    speed *= (rand() % 1000 > 500) ? -1 : 1;
    return speed;
}