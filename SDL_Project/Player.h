#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "Body.h"
#include "Window.h"
#include "Vector.h"

using namespace MATH;

class Player : public Body, public GameObject {
	friend class Collider;
public:
	Vec3 pos;
	Vec3 vel;
	Vec3 accel;

	Player();
	~Player();

	void UpdateInput(SDL_Event &event);

};

#endif

