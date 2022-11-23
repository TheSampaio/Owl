#pragma once

#include "Game.h"
#include "Graphics.h"
#include "Renderer.h"
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
	inline Renderer*& GetRenderer() const { return s_Renderer; }
	inline Window*& GetWindow()     const { return s_Window; }

	// Static methods
	static void Pause();
	static void Resume();

	// Friends
	friend Game;
	friend Sprite;
	friend Window;

private:
	int Run();
	float& GetDeltaTime();

	// Static attributes
	static bool s_bIsPaused;
	static float s_DeltaTime;

	static Input* s_Input;
	static Game* s_Game;
	static Graphics* s_Graphics;
	static Renderer* s_Renderer;
	static Window* s_Window;
	static Timer s_Timer;
};
