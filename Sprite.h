#pragma once
#include <Windows.h>



class Sprite {
private:
	RECT spriteRect;
	int x, y;
	int rx, ry;
	double t;

	int rebound = rx - 5;
	int allowedBreakBounds = 10;
	HANDLE hBitmap;
	BITMAP Bitmap;
public:
	Sprite(int _x, int _y, int _rx, int _ry, HANDLE _hBitmap, BITMAP _Bitmap);

	void moveTo(HWND& hwnd, int _x, int _y);

	boolean isInside(Sprite sprite);

	void move(HWND& hwnd, int dx, int dy);

	void correctBounds(RECT windowRect);

	void draw(HWND hwnd);
};
