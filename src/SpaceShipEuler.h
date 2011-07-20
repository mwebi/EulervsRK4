#ifndef SPACE_SHIP_EULER_H
#define SPACE_SHIP_EULER_H

#include "Body.h"

class ShipControls {
public:
	bool turnLeft, turnRight, thrust;

	ShipControls() {
		turnLeft = turnRight = thrust = false;
	}
};

class SpaceShip: public Body {
public:
	float heading;
	ShipControls *controls;
	float thrustStrength;
	int color;

	SpaceShip(bool isEulerOrRK4Ship);
	virtual ~SpaceShip();

	virtual void update(float dt,float t);
	virtual void draw();
};

#endif
