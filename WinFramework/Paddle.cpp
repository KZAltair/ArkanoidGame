#include "Paddle.h"

Paddle::Paddle(const Vec2& pos_in, int width, int height, unsigned char r, unsigned char g, unsigned char b)
	:
	pos(pos_in),
	width(width),
	height(height),
	R(r),
	G(g),
	B(b)
{
	
}

void Paddle::Draw(Graphics& gfx, int* Colors)
{
	const RectF rect = RectF::FromCenter(pos, (float)(width / 2), (float)(height / 2));
	for (int sy = (int)rect.top; sy < (int)rect.bottom; sy++)
	{
		for (int sx = (int)rect.left; sx < (int)rect.right; sx++)
		{
			gfx.DrawPixel(Colors, sx, sy, R, G, B);
		}
	}
	for (int sy = (int)rect.top; sy < (int)rect.bottom; sy++)
	{
		for (int sx = (int)rect.left + 10; sx < (int)rect.right - 10; sx++)
		{
			gfx.DrawPixel(Colors, sx, sy, 50, 125, 125);
		}
	}
}

void Paddle::Update(const Mouse& mouse, float dt)
{
	Vec2 oldPos = pos;
	pos.x = (float)(mouse.GetPosX());
	speed = (pos - oldPos).GetLength();
	vel = (pos - oldPos).Normalize();
}

bool Paddle::DoBallCollision(Ball& ball)
{
	const RectF rect = RectF::FromCenter(pos, (float)(width / 2), (float)(height / 2));
	if (rect.IsOverlappingWith(ball.GetRect()))
	{
		ball.ReboundY();
		return true;
	}
	return false;
}

void Paddle::DoWallCollision(const RectF& walls)
{
	const RectF rect = RectF::FromCenter(pos, (float)(width / 2), (float)(height / 2));
	if (rect.IsOverlappingWith(walls))
	{
		if (rect.left < walls.left)
		{
			pos.x += walls.left - rect.left;
		}
		else if (rect.right > walls.right)
		{
			pos.x -= rect.right - walls.right;
		}
	}
}

void Paddle::DoTraceCollisionTest(Ball& ball, const RectF& target, Vec2& contact_point, Vec2& contact_normal, float& contact_time, float ElapsedTime)
{
	if (cCollider.DynamicRectVsRect(ball.GetVelocity(), ball.MakeRect(), target, contact_point, contact_normal,
		contact_time, ElapsedTime))
	{
		Vec2 newVel = ball.GetVelocity();
		Vec2 ballVel = ball.GetVelocity();
		ballVel.Normalize();
		ballVel += (contact_normal * 2.0f) + vel;
		len = newVel.GetLength() + speed;
		len = std::min(len, maxSpeed);
		ballVel = (ballVel.Normalize() * len);
		ball.SetVelocity(ballVel);
	}
}

Vec2 Paddle::GetPos() const
{
	return pos;
}

RectF Paddle::GetRect() const
{
	return RectF::FromCenter(pos, (float)(width / 2), (float)(height / 2));
}
