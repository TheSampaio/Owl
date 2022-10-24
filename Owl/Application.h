#ifndef OWL_APPLICATION_H
#define OWL_APPLICATION_H

#include "PCH.h"
#include "Game.h"
#include "Window.h"

class CApplication
{
public:
	CApplication();
	~CApplication();

	// Main methods
	int Start(GGame* Game);

	// Get methods
	inline CWindow*& GetWindow() const { return s_Window; }

private:
	int Run();

	static GGame* s_Game;
	static CWindow* s_Window;
};

#endif // !OWL_APPLICATION_H
