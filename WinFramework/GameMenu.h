#pragma once
#include "UIElement.h"

class GameMenu
{
public:
	GameMenu(const RectF& size, unsigned char r, unsigned char g, unsigned char b, bool visible);
	void Draw(Graphics& gfx, int* Colors);
	void Update(const Mouse& mouse);
	bool isVisible() const;
	bool isGameQuit() const;
	void SetGameMenuVisibility(bool inFlag);
	~GameMenu();
private:
	RectF rect;
	unsigned char R;
	unsigned char G;
	unsigned char B;
	UIElement* buttonStart = nullptr;
	UIElement* buttonQuit = nullptr;
	bool isActive = false;
	bool isQuit = false;
};