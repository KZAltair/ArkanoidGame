#pragma once
#include "Graphics.h"
#include "RectF.h"
#include "Mouse.h"
#include "Ball.h"
#include "Collider.h"

class Paddle
{
public:
	Paddle(const Vec2& pos_in, int width, int height, unsigned char r, unsigned char g, unsigned char b);
	void Draw(Graphics& gfx, int* Colors);
	void Update(const Mouse& mouse, float dt);
	bool DoBallCollision(Ball& ball);
	void DoWallCollision(const RectF& walls);
	void DoTraceCollisionTest(Ball& ball, const RectF& target, Vec2& contact_point,
		Vec2& contact_normal, float& contact_time, float ElapsedTime);
	Vec2 GetPos() const;
	RectF GetRect() const;
private:
	Vec2 pos;
	Vec2 vel;
	int width;
	int height;
	float speed;
	static constexpr float maxSpeed = 1000.0f;
	float len;
	unsigned char R;
	unsigned char G;
	unsigned char B;
	Collider cCollider;
};