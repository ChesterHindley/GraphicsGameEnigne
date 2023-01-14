#pragma once
#include <Windows.h>
#include <optional>
#include <memory>
#include"Graphics.h"

class Window
{
	friend class App;
private:
	HINSTANCE hInstance;
	HWND hWin;
	int x, y;
	int xSize, ySize;
	std::unique_ptr<Graphics> gfx;
	

	
public:
	Window(HINSTANCE hinst,int x = CW_USEDEFAULT,int y = CW_USEDEFAULT,int xsize = 900,int ysize = 900);
	LRESULT HandleEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	const HWND& gethWin() const;
	std::optional<int> getMessages();
	unsigned int getxSize() const;
	unsigned int getySize() const;
};

