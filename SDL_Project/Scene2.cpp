#include "Scene2.h"
#include <SDL.h>
#include <SDL_Image.h>
#include "Body.h"
#include "Ball.h"
#include "MMAth.h"
#include "VMath.h"
#include <iostream>

Scene2::Scene2(SDL_Window* sdlwindow) {
	window = sdlwindow;
}

Scene2::~Scene2() {

}

bool Scene2::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0, 100.0, 0.0, 100.0, 0.0, 1.0);
	projection = ndc * ortho;
	ball1 = new Body(Vec3(50.0f, 50.0f, 0.0f), Vec3(-10.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f, 0.0f, 4.0f);
	ball1Image = IMG_Load("planet.png");
	ball2 = new Body(Vec3(20.0f, 50.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f, 0.0f, 4.0f);
	ball2Image = IMG_Load("star.png");

	roof = Plane(0.0f, -1.0f, 0.0f, -100.0f);
	floor = Plane(0.0f, 1.0f, 0.0f, 10.0f);
	LeftWall = Plane(1.0f, 0.0f, 0.0f, 0.0f);
	RightWall = Plane(-1.0f, 0.0f, 0.0f, -100.0f);

	return true;
}

void Scene2::OnDestroy() {
	delete ball1;
	ball1 = nullptr;

	delete ball2;
	ball2 = nullptr;

}

void Scene2::Update(const float time) {
	if (Collider::SphereSphereCollision(*ball1, *ball2)) {
		Collider::SphereSphereCollisionResponse(*ball1, *ball2);
	}
	if (Collider::SpherePlaneCollision(*ball1, floor)) {
		Collider::SpherePlaneCollisionResponse(*ball1, floor);
	}
	if (Collider::SpherePlaneCollision(*ball1, roof)) {
		Collider::SpherePlaneCollisionResponse(*ball1, roof);
	}
	if (Collider::SpherePlaneCollision(*ball1, LeftWall)) {
		Collider::SpherePlaneCollisionResponse(*ball1, LeftWall);
	}
	if (Collider::SpherePlaneCollision(*ball1, RightWall)) {
		Collider::SpherePlaneCollisionResponse(*ball1, RightWall);
	}
	if (Collider::SpherePlaneCollision(*ball2, floor)) {
		Collider::SpherePlaneCollisionResponse(*ball2, floor);
	}
	if (Collider::SpherePlaneCollision(*ball2, roof)) {
		Collider::SpherePlaneCollisionResponse(*ball2, roof);
	}
	if (Collider::SpherePlaneCollision(*ball2, LeftWall)) {
		Collider::SpherePlaneCollisionResponse(*ball2, LeftWall);
	}
	if (Collider::SpherePlaneCollision(*ball2, RightWall)) {
		Collider::SpherePlaneCollisionResponse(*ball2, RightWall);
	}

	ball1->Update(time);
	ball2->Update(time);

		
}

void Scene2::Render() {
	Vec3 ball1Pos = ball1->GetPos();
	Vec3 ball1ScreenPos = projection * ball1Pos;
	SDL_Rect dstrectball1;
	dstrectball1.x = static_cast<int>(ball1ScreenPos.x);
	dstrectball1.y = static_cast<int>(ball1ScreenPos.y);
	SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0xff));
	SDL_BlitSurface(ball1Image, nullptr, screenSurface, &dstrectball1);

	Vec3 ball2Pos = ball2->GetPos();
	Vec3 screenPosBall2 = projection * ball2Pos;
	SDL_Rect dstrectball2;
	dstrectball2.x = static_cast<int>(screenPosBall2.x);
	dstrectball2.y = static_cast<int>(screenPosBall2.y);
	SDL_BlitSurface(ball2Image, nullptr, screenSurface, &dstrectball2);

	SDL_UpdateWindowSurface(window);
}

void Scene2::HandleEvents(const SDL_Event& event) {

}
