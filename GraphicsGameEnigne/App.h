#pragma once
#include "Window.h"
#include "Graphics.h"
class App
{
	App(const App&) = delete;
	App& operator=(const App&) = delete;
	App() = delete;

private:
	Window w;
	Graphics gfx;
	void doFrame();
	
public:
	
	int Go();
	App(HINSTANCE hInst);
};

