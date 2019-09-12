#include "Game.h"
#define GAME_START_MESSAGE L"Hey. In order to conduct a revolution, you need 50 units of weapons. Collect them!"
#define GUNS_COUNT_TO_WIN 50
#define GAME_WIN_MESSAGE L"Yo've collected 50 guns. Now you can conduct a revolution. You win! But you still can go on collect guns :)"

Game::Game(Sprite* _mainSprite, Sprite* _gunSprite) {
	MessageBox(NULL, GAME_START_MESSAGE, L"So, guys. Revolution?", MB_OK);

	mainSprite = _mainSprite;
	gunSprite = _gunSprite;
}

void Game::move(HWND& hwnd, int dx, int dy)
{
	mainSprite->move(hwnd, dx, dy);

}

void Game::draw(HWND hwnd)
{
	processGame(hwnd);

	gunSprite->move(hwnd, 0, 0);
	gunSprite->draw(hwnd);

	mainSprite->move(hwnd, 0, 0);
	mainSprite->draw(hwnd);
}

void Game::processGame(HWND hwnd) {

	if (gunSprite->isInside(*mainSprite)) {
		scores++;

		RECT windowRect;
		GetClientRect(hwnd, &windowRect);

		gunSprite->moveTo(hwnd, rand() % windowRect.right, rand() % windowRect.bottom);

	}

	showScores(hwnd);

	if (scores == GUNS_COUNT_TO_WIN) {
		MessageBox(NULL, GAME_WIN_MESSAGE, L"You're awsome", MB_OK);
	}
}

Game::~Game()
{
	delete mainSprite;
	delete gunSprite;
}


void Game::showScores(HWND& hwnd) {

	int x = 0;
	int y = 0;

	RECT rect;

	rect.bottom = y + 20;
	rect.left = x;
	rect.top = y;
	rect.right = x + 100;

	InvalidateRect(hwnd, &rect, false); // redraw

	HDC hdc, hCompatibleDC;
	PAINTSTRUCT ps;

	wchar_t buffer[256];
	wsprintfW(buffer, L"%d", scores);

	hdc = BeginPaint(hwnd, &ps);
	TextOut(hdc, x, y, buffer, wcslen(buffer));
	EndPaint(hwnd, &ps);
}
