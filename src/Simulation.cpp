#include "Simulation.h"

void Simulation::setup() {
	universeSize = 10.0;
	// DONE: initialize time measuring - float time 
	time = ofGetElapsedTimef();
	
	spaceShipEuler = new SpaceShip(true);
	spaceShipEuler->thrustStrength = 10.0f;
	spaceShipEuler->controls = &cursorShipControls;
	spaceShipEuler->color = 0x0000ff;

	spaceShipRK4 = new SpaceShip(false);
	spaceShipRK4->thrustStrength = 10.0f;
	spaceShipRK4->controls = &cursorShipControls;
	spaceShipRK4->color = 0xff0000;


	ofBackground(255, 255, 255);
	ofSetVerticalSync(true);
}

void Simulation::update() {
	// DONE: measure passed time
	float t = ofGetElapsedTimef();
	float dt = t - time;
	spaceShipRK4->update(dt,t);
	spaceShipEuler->update(dt,t);
	time = t; 
}

void Simulation::draw() {
	// setup a top view for the physical universe
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);
	ofScale(ofGetWidth() / universeSize, -ofGetWidth() / universeSize, 1);

    ofSetColor(spaceShipEuler->color);
    ofDrawBitmapString("Euler Velocity X: " + ofToString(spaceShipEuler->state.velocity.x), -5,3);
    ofDrawBitmapString("Euler Velocity Y: " + ofToString(spaceShipEuler->state.velocity.y), -5,2.8);
	
	ofSetColor(0,0,0);
	ofPoint veloDiff(spaceShipEuler->state.velocity.x - spaceShipRK4->state.velocity.x,  spaceShipEuler->state.velocity.y - spaceShipRK4->state.velocity.y);
	ofDrawBitmapString("Diff Velocity visualization: ", -1,3.2);
	ofDrawBitmapString("Diff Velocity X: " + ofToString(spaceShipEuler->state.velocity.x - spaceShipRK4->state.velocity.x ), -1,3);
    ofDrawBitmapString("Diff Velocity Y: " + ofToString(spaceShipEuler->state.velocity.y - spaceShipRK4->state.velocity.y ), -1,2.8);
	
	ofPoint posDiff(spaceShipEuler->state.position.x - spaceShipRK4->state.position.x,  spaceShipEuler->state.position.y - spaceShipRK4->state.position.y);
	ofDrawBitmapString("Diff Position X: " + ofToString(posDiff.x), -1,2.5);
    ofDrawBitmapString("Diff Position Y: " + ofToString(posDiff.y), -1,2.3);
	ofDrawBitmapString("Diff Position visualization: ", -1,2.1);

	ofSetColor(spaceShipRK4->color);
	ofDrawBitmapString("RK4 Velocity X: " + ofToString(spaceShipRK4->state.velocity.x), 2.8,3);
    ofDrawBitmapString("RK4 Velocity Y: " + ofToString(spaceShipRK4->state.velocity.y), 2.8,2.8);

	// draw its only content
	spaceShipEuler->draw();
	spaceShipRK4->draw();

	ofSetColor(0,0,0);
	ofLine(0,0,spaceShipEuler->state.position.x,spaceShipEuler->state.position.y);
	ofLine(0,0,spaceShipRK4->state.position.x,spaceShipRK4->state.position.y);

	ofLine(1.3,2.1,1.3+posDiff.x,2.1+posDiff.y);
	ofLine(1.3,3.2,1.3+veloDiff.x,3.2+veloDiff.y);

}

void Simulation::handleKey(int key, bool value) {
	// handle the cursor ship controls
	switch (key) {
		case OF_KEY_LEFT:
			cursorShipControls.turnLeft = value; break;
		case OF_KEY_RIGHT:
			cursorShipControls.turnRight = value; break;
		case OF_KEY_UP:
			cursorShipControls.thrust = value; break;
	}
}

void Simulation::keyPressed(int key) {
	handleKey(key, true);
}

void Simulation::keyReleased(int key) {
	handleKey(key, false);
}

float Simulation::universeSize;