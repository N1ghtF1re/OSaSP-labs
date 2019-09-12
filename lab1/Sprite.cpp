#include "Sprite.h"

	Sprite::Sprite(int _x, int _y, int _rx, int _ry, HANDLE _hBitmap, BITMAP _Bitmap) {
			x = _x;
			y = _y;
			rx = _rx;
			ry = _ry;
			hBitmap = _hBitmap;
			Bitmap = _Bitmap;
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
		HDC hdc, hCompatibleDC;
		PAINTSTRUCT ps;
		HANDLE hOldBitmap;


		hdc = BeginPaint(hwnd, &ps);

		hCompatibleDC = CreateCompatibleDC(hdc);
		hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
		StretchBlt(hdc, x - rx, y - ry, rx * 2, ry * 2, hCompatibleDC, 13, 0, Bitmap.bmWidth - 25, 
			Bitmap.bmHeight - 5, SRCCOPY);
		SelectObject(hCompatibleDC, hOldBitmap);

		ValidateRect(hwnd, NULL);
		EndPaint(hwnd, &ps);

	}
