#pragma once
#include <Windows.h>
#include <gdiplus.h>


using namespace Gdiplus;

class Sprite {
private:
	RECT spriteRect;
	int x, y;
	int rx, ry;
	double t;

	int rebound = rx - 5;
	int allowedBreakBounds = 10;
	const WCHAR* image;
public:
	Sprite(int _x, int _y, int _rx, int _ry, const WCHAR* _image);

	void moveTo(HWND& hwnd, int _x, int _y);

	boolean isInside(Sprite sprite);

	void move(HWND& hwnd, int dx, int dy);

	void correctBounds(RECT windowRect);

	void draw(HWND hwnd);
};
