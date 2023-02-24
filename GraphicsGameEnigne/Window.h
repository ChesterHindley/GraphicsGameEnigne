#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
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
	Window(HINSTANCE hinst,int x = 350,int y = 35,int xsize = 800,int ysize = 800);
	LRESULT HandleEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	const HWND& gethWin() const;
	std::optional<int> getMessages();
	float getxSize() const;
	float getySize() const;
	int xpos;
	int ypos;
};

