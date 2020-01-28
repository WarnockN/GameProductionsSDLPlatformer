#include "Scene1.h"
#include <SDL.h>
#include <SDL_Image.h>
#include "Body.h"
#include "Ball.h"
#include "MMAth.h"
#include "VMath.h"
#include <iostream>

Scene1::Scene1(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
}

Scene1::~Scene1() {

}

bool Scene1::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0, 100.0, 0.0, 100.0, 0.0, 1.0);
	projection = ndc * ortho;
	planet = new Body(Vec3(50.0f, 50.0f, 0.0f), Vec3(-6.0f, 2.3f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f, 0.0f, 1.0f);
	planetImage = IMG_Load("planet.png");
	star1 = new Body(Vec3(20.0f, 30.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 100.0f, 0.0f, 1.0f);
	star1Image = IMG_Load("star.png");
	star2 = new Body(Vec3(80.0f, 70.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 150.0f, 0.0f, 1.0f);
	star2Image = IMG_Load("star.png");

	gravity = 11.0f;
	return true;

}

void Scene1::OnDestroy() {
	delete planet;
	planet = nullptr;
	
	delete star1;
	star1 = nullptr;

	delete star2;
	star2 = nullptr;

}

void Scene1::HandleEvents(const SDL_Event& event) {
	
}

void Scene1::Update(const float time) {
	Vec3 ps1 = star1->pos - planet->pos;
	Vec3 ps1normal = VMath::normalize(ps1);
	Vec3 forceGravity1 = ps1normal * ((gravity * planet->mass * star1->mass) / (VMath::mag(ps1) * VMath::mag(ps1)));
	Vec3 ps2 = star2->pos - planet->pos;
	Vec3 ps2normal = VMath::normalize(ps2);
	Vec3 forceGravity2 = ps2normal * ((gravity * planet->mass * star2->mass) / (VMath::mag(ps2) * VMath::mag(ps2)));
	
	Vec3 netForce = forceGravity1 + forceGravity2;	

	planet->ApplyForce(netForce);

	planet->Update(time);

}

void Scene1::Render() {
	Vec3 planetPos = planet->GetPos();
	Vec3 planetScreenPos = projection * planetPos;
	SDL_Rect dstrectPlanet;
	dstrectPlanet.x = static_cast<int>(planetScreenPos.x);
	dstrectPlanet.y = static_cast<int>(planetScreenPos.y);
	SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0xff));
	SDL_BlitSurface(planetImage, nullptr, screenSurface, &dstrectPlanet);

	Vec3 posStar1 = star1->GetPos();
	Vec3 screenPosStar1 = projection * posStar1;
	SDL_Rect dstrectStar1;
	dstrectStar1.x = static_cast<int>(screenPosStar1.x);
	dstrectStar1.y = static_cast<int>(screenPosStar1.y);
	SDL_BlitSurface(star1Image, nullptr, screenSurface, &dstrectStar1);

	Vec3 posStar2 = star2->GetPos();
	Vec3 screenPosStar2 = projection * posStar2;
	SDL_Rect dstrectStar2;
	dstrectStar2.x = static_cast<int>(screenPosStar2.x);
	dstrectStar2.y = static_cast<int>(screenPosStar2.y);
	SDL_BlitSurface(star2Image, nullptr, screenSurface, &dstrectStar2);

	SDL_UpdateWindowSurface(window);
}


