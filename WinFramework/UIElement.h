#pragma once
#include "Graphics.h"
#include "Mouse.h"

class UIElement
{
public:
	UIElement(const RectF& rect_in, unsigned char r, unsigned char g, unsigned char b, bool visible);
	void Draw(Graphics& gfx, int* Colors);
	void Update(const Mouse& mouse);
	void SetColor(unsigned char r, unsigned char g, unsigned char b);
	void SetButtonActive(bool inFlag);
	bool GetSelectedStatus() const;
	bool GetActiveStatus() const;
private:
	RectF rect;
	unsigned char R;
	unsigned char G;
	unsigned char B;
	bool isActive = false;
	bool isSelected = false;
};