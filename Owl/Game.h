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

	void SetWindow(CWindow*& Window);

protected:
	CWindow*& GetWindow();

private:
	static CWindow* s_Window;
};

#endif // !OWL_GAME_H
