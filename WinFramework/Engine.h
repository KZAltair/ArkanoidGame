#pragma once
#include "Window.h"
#include "Graphics.h"
#include "Timer.h"
#include <string>
//TODO: remake this from sleep to thread
#include <thread>
#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"

class Engine
{
public:
	Engine(class Window& wnd);
	Engine(const Engine&) = delete;
	Engine operator=(const Engine&) = delete;
	~Engine();

	void Run(class Window& wnd);
private:
	void ComposeFrame();
	void Update(class Window& wnd);
	LARGE_INTEGER EngineGetWallClock() const;
	float EngineGetSecondsElapsed(LARGE_INTEGER Start, LARGE_INTEGER End) const;
private:
	Graphics gfx;
	int* Colors;
	Timer ft;

private:
	LARGE_INTEGER PerfCountFrequecyResult;
	bool SleepIsGranular = false;
	float PerfCountFrequency;
	const float FPSMS = 1.0f / 30.0f;

	std::string winName = "Windows Framework ";
	std::string counter;
	std::string finTitle;
	float cX = 0;
private:
	//Game stuff here
	static constexpr float brickWidth = 50.0f;
	static constexpr float brickHeight = 25.0f;
	static constexpr int Rows = 4;
	static constexpr int Colls = 12;
	static constexpr int nBricks = Rows * Colls;
	Ball ball;
	Brick bricks[nBricks];
	Paddle pad;
	RectF walls;
	Brick testBrick;
	Vec2 startPos;
	Vec2 endPos;
	Vec2 cp = { 0.0f, 0.0f };
	Vec2 cn = { 0.0f, 0.0f };
	float t;
	bool collided = false;
};

/*
2. More accurate collision
3. Gameplay: start game, end game
4. Audio
5. Text, glyphs

*/