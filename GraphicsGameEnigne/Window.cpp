#include "Window.h"
#include "Graphics.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	static Window* win{ nullptr };
	if (uMsg == WM_CREATE)
		win = static_cast<Window*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
	if (win)
		return win->HandleEvent(hwnd, uMsg, wParam, lParam);
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


LRESULT Window::HandleEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) // to be called ONLY by winapi
{
	switch (uMsg) 
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

const HWND& Window::gethWin() const
{
	return hWin;
}

std::optional<int> Window::getMessages()
{
	MSG msg;
	while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {

		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
			return static_cast<int>(msg.wParam);
	}
		return std::optional<int>();
	
}

Window::Window(HINSTANCE hinst, int x, int y, int xsize, int ysize)	 // most likely x and y values assigned are wrong, assign at the end
	: hInstance{ hinst }, x{ x }, y{ y }
{
	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = "basicWC";


	RECT rect{.left = 0,.top = 0,.right = xsize, .bottom = ysize};
	AdjustWindowRect(&rect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE, false);

	RegisterClass(&wc);
	hWin = CreateWindow("basicWC", "GraphicsGameEngine", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE, x, y, rect.right-rect.left, rect.bottom-rect.top, NULL, NULL, hInstance, this); // last null is what i ll tinker later 
	xSize = xsize;
	ySize = ysize;


	gfx = std::make_unique<Graphics>(*this); // alignment problem for cbuffer because of heap allocation or sth

}
float Window::getxSize() const { return xSize; }
float Window::getySize() const { return ySize; } 