#ifndef OWL_GAME_H
#define OWL_GAME_H

#include "Window.h"

class Game
{
public:
	Game();
	virtual ~Game();

	virtual void OnPause();

	virtual void Start()				  PURE;
	virtual void Update(float& DeltaTime) PURE;
	virtual void Draw()					  PURE;
	virtual void Finish()				  PURE;

	inline void SetWindow(Window*& Window) { s_Window = Window; s_Input = s_Window->GetInput(); }

protected:
	inline Input*& GetInput() const { return s_Input; }
	inline Window*& GetWindow() const { return s_Window; }

private:
	static Input* s_Input;
	static Window* s_Window;
};

#endif // !OWL_GAME_H
