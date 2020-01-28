#ifndef BODY_H
#define BODY_H
#include "Vector.h"
#include <SDL.h>

using namespace MATH; 

class Body {
	friend class Collider;
public:
	Vec3 pos;
	Vec3 vel;
	Vec3 accel;
	float mass;
	float time;
	float nforce;	
	float radius;


	Body();
	~Body();
	Body(Vec3 pos_, Vec3 vel, Vec3 accel_, float mass_, float time_, float radius_);
	void Update(const float deltaTime);
	void ApplyForce(Vec3 force);
	Vec3 GetPos();
	Vec3 GetVel();
	void SetVel(float number_);
};

#endif
