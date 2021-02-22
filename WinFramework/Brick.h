#pragma once
#include "RectF.h"
#include "Graphics.h"
#include "Ball.h"

class Brick
{
public:
	Brick() = default;
	Brick(const RectF& rect_in, unsigned char r, unsigned char g, unsigned char b);
	void Draw(Graphics& gfx, int* Colors);
	bool DoBallCollision(Ball& ball);
	bool RayVsRectCollision(const Vec2& ray_origin, const Vec2& ray_dir, const RectF& target,
		Vec2& contact_point, Vec2& contact_normal, float& t_hit_near);
private:
	RectF rect;
	static constexpr float padding = 1.0f;
	unsigned char R;
	unsigned char G;
	unsigned char B;
	bool destroyed = false;
};