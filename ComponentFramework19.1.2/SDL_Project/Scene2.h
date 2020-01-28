#ifndef SCENE2_H
#define SCENE2_H

#include "Scene.h"

#include "MMath.h"
#include <SDL.h>
#include "Body.h"
#include "Ball.h"
#include "Collider.h"

class Scene2 : public Scene {
private:
	SDL_Window* window;
	Body* ball1;
	SDL_Surface* ball1Image;
	Body* ball2;
	SDL_Surface* ball2Image;

	Plane roof;
	Plane floor;
	Plane LeftWall;
	Plane RightWall;

	float time;
	float gravity;
	Matrix4 projection;

public:
	Scene2(SDL_Window* sdlwindow);
	~Scene2();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& event);
};

#endif
