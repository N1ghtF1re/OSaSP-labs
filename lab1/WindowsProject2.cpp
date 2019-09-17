#include <windows.h>
#include <tchar.h>
#include <cmath>
#include <cstdlib>
#include "Sprite.h"
#include "Game.h"

#define FILE_NOT_FOUND L"File not found!"
#define MAIN_SPRITE_PATH  L"Che.bmp"
#define GUN_SPRITE_PATH L"Gun1.bmp"
#define WINDOW_TITLE L"Osisp lab1"
#define TIMER_TIME 40

LRESULT CALLBACK  WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
TCHAR WinName[] = _T("MainFrame");

Game *game;

RECT rc;

#include<gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;


class Window {
public:
	HWND hwnd;              // Window's descriptor
	MSG msg;               
	WNDCLASS wc; 

	bool reg_window(HINSTANCE This, LPCWSTR lpzClassName, WNDPROC lpfnWndProc) {
		wc.hInstance = This;
		wc.lpszClassName = WinName;                
		wc.lpfnWndProc = WndProc;                 
		wc.style = CS_HREDRAW | CS_VREDRAW;       
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);  
		wc.hCursor = LoadCursor(NULL, IDC_ARROW); 
		wc.lpszMenuName = NULL;       
		wc.cbClsExtra = 0;            
		wc.cbWndExtra = 0;            // White color
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		HBRUSH hb = ::CreateSolidBrush(RGB(222, 10, 249));
		wc.hbrBackground = hb;
		if (!RegisterClass(&wc)) return 0;  

	}

	void create_window(HINSTANCE This) {
		hwnd = CreateWindow(WinName, //
			WINDOW_TITLE,  
			WS_OVERLAPPEDWINDOW,       
			0, // x
			0, // y   
			1000, // width
			600, // Height
			HWND_DESKTOP, 
			NULL,         // Without menu
			This,         // Application descriptor
			NULL);        

		GetWindowRect(hwnd, &rc);
	}

	void show_window() {
		ShowWindow(hwnd, SW_SHOW); 
	}

};


// SPEED: 
static int vx = 10;
static int vy = 10;

int WINAPI _tWinMain(HINSTANCE This, 
	HINSTANCE,      
	LPTSTR,         
	int mode)       
{
	// Часть кода GDI+:
	GdiplusStartupInput gdiplusStartupInput; // Связано с загрузкой картинки
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL); // Включаем GDI+

	Sprite* mainSprite, * gunSprite;


	BITMAP Bitmap;
	HANDLE hBitmap = LoadImage(NULL, MAIN_SPRITE_PATH, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (!hBitmap) {
		MessageBox(NULL, FILE_NOT_FOUND, L"Error", MB_OK);
		return 0;
	}
	GetObject(hBitmap, sizeof(BITMAP), &Bitmap);

	mainSprite = new Sprite(40, 40, 30, 40, L"C:\\Users\\User\\Source\\Repos\\WindowsProject2\\Debug\\image.png");

	hBitmap = LoadImage(NULL, GUN_SPRITE_PATH, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (!hBitmap) {
		MessageBox(NULL, FILE_NOT_FOUND, L"Error", MB_OK);
		return 0;
	}
	GetObject(hBitmap, sizeof(BITMAP), &Bitmap);

	gunSprite = new Sprite(100, 100, 10, 10, L"C:\\Users\\User\\Source\\Repos\\WindowsProject2\\Debug\\image.png");

	game = new Game(mainSprite, gunSprite);


	MSG msg;
	Window myWin;


	myWin.reg_window(This, L"MyWindowClass", WndProc);
	myWin.create_window(This);
	myWin.show_window();

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 
		DispatchMessage(&msg);  
	}
	GdiplusShutdown(gdiplusToken); // Завершение работы GDI+
	return 0;
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_KEYDOWN:
			switch (wParam) {
			case VK_LEFT:
				game->move(hwnd, -vx, 0);
				break;

			case VK_RIGHT:
				game->move(hwnd, vx, 0);
				break;

			case VK_UP:
				game->move(hwnd, 0, -vy);
				break;

			case VK_DOWN:
				game->move(hwnd, 0, vy);
				break;

			case VK_SPACE: 
				SetTimer(hwnd, 1, TIMER_TIME, 0);
				break;
			case VK_ESCAPE:
				KillTimer(hwnd, 1);
				break;
			}

			break;

		case WM_MOUSEWHEEL:
		{
			int key = GET_KEYSTATE_WPARAM(wParam);
			int delta = GET_WHEEL_DELTA_WPARAM(wParam);

			if (delta > 0) {
				if (key == MK_SHIFT) {
					game->move(hwnd, vx, 0);
				}
				else {
					game->move(hwnd, 0, vy);
				}
			}
			else {
				if (key == MK_SHIFT) {
					game->move(hwnd, -vx, 0);
				}
				else {
					game->move(hwnd, 0, -vy);
				}
			}
		}
			break;	

		case WM_PAINT:
		{

			game->draw(hwnd);

		}
			break;

		case WM_TIMER:
			game->move(hwnd, rand() % 11 - 5, rand() % 11 - 5);
			break;

		case WM_DESTROY:
			delete game;
			PostQuitMessage(0);
			break;

		default:
			return (DefWindowProc(hwnd, message, wParam, lParam));
	}
}