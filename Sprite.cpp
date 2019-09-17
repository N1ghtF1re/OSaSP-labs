#include "Sprite.h"
#include <gdiplus.h>


using namespace Gdiplus;


	Sprite::Sprite(int _x, int _y, int _rx, int _ry, const WCHAR* _image) {
			x = _x;
			y = _y;
			rx = _rx;
			ry = _ry;
			image = _image;
	}

	void Sprite::moveTo(HWND& hwnd, int _x, int _y) {
		InvalidateRect(hwnd, &spriteRect, true); // Remove sprite from screen
		x = _x;
		y = _y;

		RECT windowRect;
		GetClientRect(hwnd, &windowRect);
		correctBounds(windowRect);


		spriteRect.left = x - rx - 1;
		spriteRect.top = y - ry - 1;
		spriteRect.right = x + rx + 1;
		spriteRect.bottom = y + ry + 1;

		InvalidateRect(hwnd, &spriteRect, false); // redraw
	}

	boolean Sprite::isInside(Sprite sprite) {
		return x - rx > sprite.x - sprite.rx
			&& x + rx < sprite.x + sprite.rx
			&& y - ry > sprite.y - sprite.ry
			&& y + ry < sprite.y + sprite.ry;
	}

	void Sprite::move(HWND& hwnd, int dx, int dy) {
		InvalidateRect(hwnd, &spriteRect, true); // Remove sprite from screen
		x += dx; y += dy;

		RECT windowRect;
		GetClientRect(hwnd, &windowRect);
		correctBounds(windowRect);


		spriteRect.left = x - rx - 1;
		spriteRect.top = y - ry - 1;
		spriteRect.right = x + rx + 1;
		spriteRect.bottom = y + ry + 1;

		InvalidateRect(hwnd, &spriteRect, false); // redraw

	}

	void Sprite::correctBounds(RECT windowRect) {
		if (x + rx > windowRect.right + allowedBreakBounds)
			x -= rebound + rx;
		if (x - rx < -allowedBreakBounds)
			x += rebound + rx;
		if (y + ry > windowRect.bottom + allowedBreakBounds)
			y -= rebound + ry;
		if (y - ry < -allowedBreakBounds)
			y += rebound + ry;
	}

	void Sprite::draw(HWND hwnd) {
		RECT rc;
		GetWindowRect(hwnd, &rc);

		PAINTSTRUCT pt;

		HDC hDC = BeginPaint(hwnd, &pt);

		Graphics graphics(hDC);
		Bitmap BackBuf(rc.right, rc.bottom, &graphics);
		Graphics temp(&BackBuf);

		Image img = image;

		temp.DrawImage(&img, x, y, rx, ry);

		graphics.DrawImage(&BackBuf, 0, 0, 0, 0, rc.right, rc.bottom, UnitPixel);

		EndPaint(hwnd, &pt);


	}
