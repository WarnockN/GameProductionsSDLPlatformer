#include "Collider.h"
#include "VMath.h"
#include <iostream>


bool Collider::SphereSphereCollision(const Body& ball1, const Body& ball2) {
	Vec3 center1 = ball1.pos;
	Vec3 center2 = ball2.pos;
	float distance = VMath::distance(center1, center2); 
	
	if (distance < (ball1.radius + ball2.radius)) {
		return true;
	}
	return false;
}

void Collider::SphereSphereCollisionResponse(Body& ball1, Body& ball2) {
	float e = 1.0f; //Coefficient of Restitution
	Vec3 lineOfAction = ball1.pos - ball2.pos;
	Vec3 normalLineOfAction = VMath::normalize(lineOfAction);

	float v1p = VMath::dot(normalLineOfAction, ball1.vel);
	float v2p = VMath::dot(normalLineOfAction, ball2.vel);
	
	float v1pnew = ((ball1.mass - e * ball2.mass) * v1p) + ((1.0f + e) * ball2.mass * v2p) / (ball1.mass + ball2.mass);
	float v2pnew = ((ball2.mass - e * ball1.mass) * v2p) + ((1.0f + e) * ball1.mass * v1p) / (ball1.mass + ball2.mass);

	if (v1p - v2p > 0.0f) return;
	ball1.vel += (v1pnew - v1p) * normalLineOfAction;
	ball2.vel += (v2pnew - v2p) * normalLineOfAction;
}

bool Collider::SpherePlaneCollision(const Body& ball, const Plane& plane) {
	if (VMath::distance(ball.pos, plane) < (ball.radius)) {
		return true;
	}
	return false;
}

void Collider::SpherePlaneCollisionResponse(Body& ball, const Plane& plane) {
	if (VMath::dot(ball.vel, plane) >= 0.0f) {
		return;
	}
	float magnitude = VMath::mag(ball.vel);
	Vec3 normalVelocity = VMath::normalize(ball.vel);
	Vec3 reflection = VMath::reflect(normalVelocity, plane);
	ball.vel = reflection * magnitude;
	

}
