#include "App.h"

int WINAPI wWinMain(HINSTANCE hInstance,
	[[maybe_unused]] HINSTANCE  hPrevInstance,
	[[maybe_unused]] PWSTR pCmdLine,
	[[maybe_unused]] int nCmdShow)
{
	return App(hInstance).Go();
}
