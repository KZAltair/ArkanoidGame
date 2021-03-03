#pragma once
#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"

class ArkanoidGame
{
public:
	ArkanoidGame(int numLives);
	~ArkanoidGame();
	void Update(float dt, const Mouse&);
	void Draw(Graphics& gfx, int* Colors);
	bool isGameOver() const;

private:
	static constexpr float brickWidth = 50.0f;
	static constexpr float brickHeight = 25.0f;
	static constexpr int Rows = 4;
	static constexpr int Colls = 12;
	static constexpr int nBricks = Rows * Colls;
	Ball* ball = nullptr;
	Brick* bricks = nullptr;
	Paddle* pad = nullptr;
	RectF walls;
	bool clicked = false;
	bool gameOver = false;
	int lives = 0;
	float wait = 0.0f;
	int numBricks = 0;
};