#ifndef OWL_APPLICATION_H
#define OWL_APPLICATION_H

#include "Game.h"
#include "Graphics.h"
#include "Window.h"

class CApplication
{
public:
	CApplication();
	~CApplication();

	// Main methods
	int Start(GGame* Game);

	// Get methods
	inline RGraphics*& GetGraphics() const { return s_Graphics; }
	inline CWindow*& GetWindow() const { return s_Window; }

private:
	int Run();

	static GGame* s_Game;
	static RGraphics* s_Graphics;
	static CWindow* s_Window;
};

#endif // !OWL_APPLICATION_H
