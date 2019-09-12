#pragma once
#include "Sprite.h"

class Game
{
private:
	Sprite* mainSprite;
	Sprite* gunSprite;
	int scores;
	void showScores(HWND& hwnd);
public:
	Game(Sprite* _mainSprite, Sprite* _gunSprite);
	void move(HWND& hwnd, int dx, int dy);
	void draw(HWND hwnd);
	void processGame(HWND hwnd);
	~Game();
};

