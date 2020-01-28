#include "Assignment.h"

Assignment::Assignment(Vec3 gravAccel_) {
	elapsedTime = 0.0f;
	gravAccel.x = gravAccel_.x;
	gravAccel.y = gravAccel_.y;
	gravAccel.z = gravAccel_.z;
}

Assignment::~Assignment() {
	delete bodies[0];
	delete bodies[1];
	*bodies = nullptr;
}

void Assignment::AddTwoBodies(Body* ball1, Body* ball2) {
	bodies[0] = ball1;
	bodies[1] = ball2;
}

void Assignment::Update(float deltaTime) {
	bodies[0]->accel.y += gravAccel.y;
	bodies[1]->accel.y += gravAccel.y;

	bodies[0]->Update(deltaTime);
	bodies[1]->Update(deltaTime);

	elapsedTime += deltaTime;
}
