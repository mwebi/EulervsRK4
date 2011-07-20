#ifndef SIMULATION_H
#define SIMULATION_H

#include "ofMain.h"
#include "SpaceShipEuler.h"

class Simulation: public ofBaseApp {
public:	
	static float universeSize;
	float time;
	SpaceShip *spaceShipEuler;
	SpaceShip *spaceShipRK4;
	ShipControls cursorShipControls;

	void setup();
	void update();

	void draw();
	void handleKey(int key, bool value);
	void keyPressed(int key);
	void keyReleased(int key);
};

#endif
