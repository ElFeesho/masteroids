Masteroids
==========
[![Build Status](https://travis-ci.org/ElFeesho/masteroids.svg?branch=master)](https://travis-ci.org/ElFeesho/masteroids)

Masteroids is a multiplayer implementation of the Atari classic, Asteroids. Masteroids originally was compiled and built for the Nintendo Wii. 

I am now starting to port the game to PC.

Plans
-----
1. Refactor & simplify code base
2. Pull out inter-twined classes
3. Add NETWORK PLAY
4. Test on wii...
5. NETWORK PLAY BETWEEN WII AND PC...
6. ???
7. Android port

Progress
--------
So far a lot of the inheritance (all?) has been removed and control and knowledge has been centralised a bit better into 'Screen' instances.
Moving towards a set of factories that produce asteroids or ships.
Input needs some serious re-work though!
