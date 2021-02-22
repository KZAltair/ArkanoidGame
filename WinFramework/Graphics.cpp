#include "Graphics.h"
#include <iostream>
#include <assert.h>

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}

void Graphics::FillScreenFast(int* Colors, unsigned char r, unsigned char g, unsigned char b)
{
	for (int* i = Colors, *end = &Colors[800 * 600]; i < end; i++)
	{
		*i = (r << 16) | (g << 8) | b;
	}
}

void Graphics::ClearScreenSuperFast(int* Colors)
{
	std::memset(Colors, 0, 800 * 600 * 4);
}

void Graphics::DrawPixel(int* Colors, int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
	assert(x >= 0);
	assert(x <= 800);
	assert(y >= 0);
	assert(y <= 600);
	Colors[y * 800 + x] = (r << 16) | (g << 8) | b;
}

void Graphics::DrawLine(int* Colors, Vec2 p0, Vec2 p1, unsigned char r, unsigned char g, unsigned char b)
{
	float m = 0.0f;

	if (p1.x != p0.x)
	{
		m = (p1.y - p0.y) / (p1.x - p0.x);
	}

	if (p1.x != p0.x && std::abs(m) <= 1.0f)
	{
		if (p0.x > p1.x)
		{
			std::swap(p0, p1);
		}

		const float b = p0.y - m * p0.x;

		for (int x = (int)p0.x; x < (int)p1.x; x++)
		{
			const float y = m * (float)x + b;
			DrawPixel(Colors, x, (int)y, r, g, b);
		}
	}
	else
	{
		if (p0.y > p1.y)
		{
			std::swap(p0, p1);
		}
		const float w = (p1.x - p0.x) / (p1.y - p0.y);
		const float p = p0.x - w * p0.y;

		for (int y = (int)p0.y; y < (int)p1.y; y++)
		{
			const float x = w * (float)y + p;
			DrawPixel(Colors, (int)x, y, r, g, b);
		}
	}
}

