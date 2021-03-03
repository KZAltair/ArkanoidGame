#include "Brick.h"
#include <cmath>
#include <algorithm>

Brick::Brick(const RectF& rect_in, unsigned char r, unsigned char g, unsigned char b)
	:
	rect(rect_in),
	R(r),
	G(g),
	B(b)
{
}

void Brick::Draw(Graphics& gfx, int* Colors)
{
	if (!destroyed)
	{
		for (int sy = (int)(rect.top + padding); sy < (int)(rect.bottom - padding); sy++)
		{
			for (int sx = (int)(rect.left + padding); sx < (int)(rect.right - padding); sx++)
			{
				gfx.DrawPixel(Colors, sx, sy, R, G, B);
			}
		}
	}
}

bool Brick::DoBallCollision(Ball& ball)
{
	if (!destroyed && rect.IsOverlappingWith(ball.GetRect()))
	{
		ball.ReboundY();
		destroyed = true;
		return true;
	}
	return false;
}

bool Brick::RayVsRectCollision(const Vec2& ray_origin, const Vec2& ray_dir, const RectF& target, Vec2& contact_point, Vec2& contact_normal, float& t_hit_near)
{
	Vec2 t_near = (target.GetPos() - ray_origin) / ray_dir;
	Vec2 t_far = (Vec2(target.right, target.bottom) - ray_origin) / ray_dir;

	if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
	if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

	if (t_near.x > t_far.y || t_near.y > t_far.x) return false;
	t_hit_near = std::max(t_near.x, t_near.y);
	float t_hit_far = std::min(t_far.x, t_far.y);

	if (t_hit_far < 0.0f) return false;

	contact_point = ray_origin + ray_dir * t_hit_near;

	if (t_near.x > t_near.y)
	{
		if (ray_dir.x < 0)
		{
			contact_normal = { 1.0f, 0.0f };
		}
		else
		{
			contact_normal = { -1.0f, 0.0f };
		}
	}
	else if (t_near.x < t_near.y)
	{
		if (ray_dir.y < 0)
		{
			contact_normal = { 0.0f, 1.0f };
		}
		else
		{
			contact_normal = { 0.0f, -1.0f };
		}
	}

	return true;
}

bool Brick::DynamicRectVsRect(const Vec2& vel, const RectF& rect_in, const RectF& target, Vec2& contact_point, Vec2& contact_normal, float& contact_time, float ElapsedTime)
{
	//Vel of the moving rect
	if (vel.x == 0.0f && vel.y == 0.0) return false;

	Vec2 expPos = target.GetPos() - Vec2((rect_in.right - rect_in.left) / 2, (rect_in.bottom - rect_in.top) / 2);
	Vec2 expSize = Vec2(target.right, target.bottom) + Vec2((rect_in.right - rect_in.left) / 2, (rect_in.bottom - rect_in.top) / 2);
	expanded_target = RectF(expPos, expSize);

	if (RayVsRectCollision(rect_in.GetCenter(), vel * ElapsedTime, expanded_target, contact_point, contact_normal, contact_time))
	{

		if (contact_time <= 1.0f)
		{
			return true;
		}
	}
	return false;
}

bool Brick::DoTraceCollisionTest(Ball& ball, const RectF& target, Vec2& contact_point, Vec2& contact_normal, float& contact_time, float ElapsedTime)
{
	if (!destroyed)
	{
		if (DynamicRectVsRect(ball.GetVelocity(), ball.MakeRect(), target, contact_point, contact_normal,
			contact_time, ElapsedTime))
		{
			Vec2 newVel = ball.GetVelocity();
			Vec2 ballVel = ball.GetVelocity();
			ballVel.Normalize();
			ballVel += contact_normal * 2.0f;
			float len = newVel.GetLength();
			ballVel = ballVel.Normalize() * len;
			ball.SetVelocity(ballVel);
			destroyed = true;
			return true;
		}
	}
	return false;
}

RectF Brick::GetOriginalRect() const
{
	return rect;
}

