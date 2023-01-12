#include "App.h"

void App::doFrame()
{
	w.gfx.get()->endFrame();
	w.gfx.get()->drawTriangle();

}

int App::Go()
{
	while (true)
	{
		if (auto ret = w.getMessages()) return ret.value();
		doFrame();
	}

}

App::App(HINSTANCE hInst) :w(hInst)
{
}
