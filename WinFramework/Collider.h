#pragma once
#include "RectF.h"

class Collider
{
public:
	Collider() = default;
	bool RayVsRectCollision(const Vec2& ray_origin, const Vec2& ray_dir, const RectF& target,
		Vec2& contact_point, Vec2& contact_normal, float& t_hit_near);
	bool DynamicRectVsRect(const Vec2& vel, const RectF& rect_in, const RectF& target,
		Vec2& contact_point, Vec2& contact_normal, float& contact_time, float ElapsedTime);
private:

};