#include "SpaceShipEuler.h"

SpaceShip::SpaceShip(bool isEulerOrRK4Ship): Body(isEulerOrRK4Ship) {
	heading = PI / 2;
}

SpaceShip::~SpaceShip() {
}

void SpaceShip::update(float dt,float t) {
	if (controls->turnLeft) heading += 0.04;
	if (controls->turnRight) heading -= 0.04;

	float thrustMagnitude = controls->thrust ? thrustStrength : 0.0f;

	// apply thrust force:
	applyForce(ofPoint(cos(heading), sin(heading)) * thrustMagnitude);
	
    // apply gravitational force:
	// applyForce(ofPoint(0.0f, -9.81f) * mass);

	Body::update(dt,t);
}

void SpaceShip::draw() {
	// draw a simple triangle as our spaceship
	ofPushMatrix();
	ofTranslate(state.position.x, state.position.y, 0);
	
	ofRotateZ(heading / PI * 180);
	ofFill();
	ofSetColor(color);
	ofBeginShape();
		ofVertex(0.3, 0);
		ofVertex(-0.1,-0.1);
		ofVertex(-0.1,+0.1);
	ofEndShape();
	ofPopMatrix();
}
