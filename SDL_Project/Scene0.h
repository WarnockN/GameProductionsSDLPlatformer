#ifndef SCENE0_H
#define SCENE0_H

#include "MMath.h"
#include "Scene.h"
#include <SDL.h>
#include "Body.h"
#include "Ball.h"

using namespace MATH;
class Scene0 : public Scene {
private:
	//Ball* jetski;
	SDL_Window *window;
	Body* jetski;
	SDL_Surface* jetskiImage;
	Matrix4 projection;
	float timer;
public:
	Scene0(SDL_Window* sdlWindow);
	~Scene0();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& event);
};
#endif

