#pragma once
#include "Window.h"

class App
{
	App(const App&) = delete;
	App& operator=(const App&) = delete;
	App() = delete;

private:
	Window w;
	void doFrame();
	
public:
	
	int Go();
	App(HINSTANCE hInst);
};

