#ifndef OWL_GAME_H
#define OWL_GAME_H

#include "Window.h"

class GGame
{
public:
	GGame();
	virtual ~GGame();

	virtual void OnPause();

	virtual void Start()				 PURE;
	virtual void Update(float DeltaTime) PURE;
	virtual void Draw()					 PURE;
	virtual void Finish()				 PURE;

	inline void SetWindow(CWindow*& Window) { s_Window = Window; }

protected:
	inline CWindow*& GetWindow() const { return s_Window; }

private:
	static CWindow* s_Window;
};

#endif // !OWL_GAME_H
