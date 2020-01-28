#ifndef BALL_H
#define BALL_H

#include "Body.h"
#include "GameObject.h"

//Public
//Private
//Protected

class Ball : public Body, public GameObject {

public:
	Ball();
	~Ball();
	SDL_Surface* image;

	bool OnCreate() = 0;
	void OnDestroy() = 0;
	void Update(const float deltaTime) = 0;
	void Render() const = 0;
	void HandleEvents(const SDL_Event& sdlEvent) = 0;

};

#endif
	


