#include "Window.h"
#include "Graphics.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	static Window* win{ nullptr };
	if (uMsg == WM_CREATE)
		win = static_cast<Window*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
	if (win)
		return win->HandleEvent(hwnd, uMsg, wParam, lParam); // won't HandleEvent be problematic if DefWindowProc hasn't been done for WM_CREATE
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

Window::Window(HINSTANCE hinst, int x, int y, int xsize, int ysize)		// MASSIVE TODO: AdjustWindowRect() since width and height I give are not the ones used for user space
	: hInstance{ hinst }, x{ x }, y{ y }, xSize{ xsize }, ySize{ ysize }
{
	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = "basicWC";

	RegisterClass(&wc);
	hWin = CreateWindow("basicWC", "GraphicsGameEngine", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE, x, y, xSize, ySize, NULL, NULL, hInstance, this); // last null is what i ll tinker later 

	gfx = std::make_unique<Graphics>(*this);

}
unsigned int Window::getxSize() const { return xSize; }
unsigned int Window::getySize() const { return ySize; } 