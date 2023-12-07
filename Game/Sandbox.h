#ifndef SANDBOX_GAME

#include "Owl.h"

class Sandbox : public owl::Game
{
public:
	Sandbox();

	void OnStart();
	void OnUpdate();
	void OnDraw();
	void OnFinalize();
};

#endif // !SANDBOX_GAME
