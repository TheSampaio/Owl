#ifndef OWL_APPLICATION_H
#define OWL_APPLICATION_H

#include "Game.h"
#include "Graphics.h"
#include "Timer.h"
#include "Window.h"

class Application
{
public:
	Application();
	~Application();	

	// Main methods
	int Start(Game* Game);

	// Get methods
	inline Graphics*& GetGraphics() const { return s_Graphics; }
	inline Window*& GetWindow() const	   { return s_Window; }

	// Static methods
	static void Pause();
	static void Resume();

private:
	int Run();
	float& GetDeltaTime();

	// Static attributes
	static bool s_bIsPaused;
	static float s_DeltaTime;

	static Input* s_Input;
	static Game* s_Game;
	static Graphics* s_Graphics;
	static Timer s_Timer;
	static Window* s_Window;
};

#endif // !OWL_APPLICATION_H
