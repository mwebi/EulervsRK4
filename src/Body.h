#ifndef BODY_H
#define BODY_H

#include "ofMain.h"


struct State
{
	ofPoint position;
	ofPoint velocity;
};

struct Derivative
{
	ofPoint dx;
	ofPoint dv;
};

// this abstract is used by all bodies participating in the physical simulation
class Body {
public:
	State state;
	ofPoint position;
	ofPoint velocity;
	ofPoint springForce;
	float mass;
	ofPoint force;
	bool useEulerOrRK4;

	Body(bool isEulerOrRK4Ship);
	// we have to declare a virtual destructor
	virtual ~Body();

	// update the body with a simulation time step of dt
	virtual void update(float dt,float t);
	// draw the body
	virtual void draw() = 0;
	virtual void applyForce(ofPoint const &force);

	//RK4 methods
	ofPoint acceleration(const State &state, float t);
	Derivative evaluate(const State &initial, float t);
	Derivative evaluate(const State &initial, float t, float dt, const Derivative &d);
};

#endif
