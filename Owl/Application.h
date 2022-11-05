#ifndef OWL_APPLICATION_H
#define OWL_APPLICATION_H

#include "Game.h"
#include "Graphics.h"
#include "Timer.h"
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
	inline CWindow*& GetWindow() const	   { return s_Window; }

	// Static methods
	static void Pause();
	static void Resume();

private:
	int Run();
	float& GetDeltaTime();

	// Static attributes
	static bool s_bIsPaused;
	static float s_DeltaTime;

	static GGame* s_Game;
	static RGraphics* s_Graphics;
	static ITimer s_Timer;
	static CWindow* s_Window;
};

#endif // !OWL_APPLICATION_H
