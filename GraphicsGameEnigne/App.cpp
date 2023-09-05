#include "App.h"

void App::doFrame()
{
	gfx.endFrame();
	gfx.drawTriangle();

}

int App::Go()
{
	while (true)
	{
		if (auto ret = w.getMessages()) return ret.value();
		doFrame();
	}

}

App::App(HINSTANCE hInst) :w(hInst), gfx(w)
{
}
