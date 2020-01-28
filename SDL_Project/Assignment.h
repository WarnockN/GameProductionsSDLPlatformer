#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "Body.h"

class Assignment {
public:
	Body* bodies[2];
	float elapsedTime;
	Vec3 gravAccel;

	Assignment(Vec3 gravAccel_);
	~Assignment();

	void AddTwoBodies(Body* ball1, Body* ball2);
	void Update(float deltaTime);
};

#endif
