#pragma once

#include "Window.h"

class Game
{
public:
	Game() {};
	virtual ~Game() {};

	virtual void OnPause();

	virtual void Start()				  PURE;
	virtual void Update(float& DeltaTime) PURE;
	virtual void Draw()					  PURE;
	virtual void Finish()				  PURE;

protected:
	inline Input*& GetInput()   const { return s_Input; }
	inline Window*& GetWindow() const { return s_Window; }

private:
	static Input*& s_Input;
	static Window*& s_Window;
};
