#pragma once
#include "Graphics.h"
#include "Vec2.h"
#include "RectF.h"

class Ball
{
public:
	Ball(const Vec2& pos_in, const Vec2& vel_in);
	~Ball();
	bool DoWallCollision(const RectF& walls);
	void ReboundX();
	void ReboundY();
	RectF GetRect() const;
	void Draw(Graphics& gfx, int* Colors);
	void Update(float dt);
	Vec2 GetVelocity()const;
	void SetVelocity(Vec2 vel_in);
	RectF MakeRect() const;

private:
	static constexpr float radius = 5.0f;
	Vec2 pos;
	Vec2 vel;
};