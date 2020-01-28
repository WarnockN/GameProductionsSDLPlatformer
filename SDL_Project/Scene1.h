#ifndef SCENE1_H
#define SCENE1_H

#include "Scene.h"

#include "MMath.h"
#include "Scene.h"
#include <SDL.h>
#include "Body.h"
#include "Ball.h"

class Scene1 : public Scene {
private:
	SDL_Window* window;
	Body* planet;
	SDL_Surface* planetImage;
	Body* star1;
	SDL_Surface* star1Image;
	Body* star2;
	SDL_Surface* star2Image;
	float time;
	float gravity;
	Matrix4 projection;

public:
	Scene1(SDL_Window* sdlwindow);
	~Scene1();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& event);
};

#endif