#include "Body.h"
#include "Simulation.h"

Body::Body(bool isEulerOrRK4Ship): mass(1.0f) {

	useEulerOrRK4=isEulerOrRK4Ship;
	if(useEulerOrRK4){
		state.position = ofPoint(1.0f, 1.0f);
		state.velocity = ofPoint(0.0f, 0.0f);

	}else{
		state.position = ofPoint(1.0f, 1.0f);
		state.velocity = ofPoint(0.0f, 0.0f);
	}
}

Body::~Body() {
}



ofPoint Body::acceleration(const State &state, float t)
{
	ofPoint acceleration = force / mass; 

	return acceleration; 
}

Derivative Body::evaluate(const State &initial, float t)
{
	Derivative output;
	output.dx = initial.velocity;
	output.dv = acceleration(initial, t);
	return output;
}

Derivative Body::evaluate(const State &initial, float t, float dt, const Derivative &d)
{
	State state;
	state.position = initial.position + d.dx*dt;
	state.velocity = initial.velocity + d.dv*dt;
	Derivative output;
	output.dx = state.velocity;
	output.dv = acceleration(state, t+dt);
	return output;
}


void Body::update(float dt, float t) {
	const float k = 10;
	const float b = 1;
	springForce = state.position*-k + state.velocity*-b;
	applyForce(springForce);

	if(useEulerOrRK4){
		//euler
		ofPoint acceleration = force / mass; 

		state.velocity += acceleration * dt;
		state.position += state.velocity * dt;


	}else{
		//RK4
		Derivative a = evaluate(state, t);
		Derivative b = evaluate(state, t, dt*0.5f, a);
		Derivative c = evaluate(state, t, dt*0.5f, b);
		Derivative d = evaluate(state, t, dt, c);

		ofPoint dxdt = (a.dx + (b.dx + c.dx)*2.0f + d.dx)*1.0f/6.0f;
		ofPoint dvdt = (a.dv + (b.dv + c.dv)*2.0f + d.dv)*1.0f/6.0f;
		
		
		state.velocity = state.velocity + dvdt*dt;
		state.position = state.position + dxdt*dt;
	}


	// reset for next frame
	force = ofPoint(0.0f, 0.0f);	
}

void Body::applyForce(ofPoint const &force) {
	this->force += force;
}