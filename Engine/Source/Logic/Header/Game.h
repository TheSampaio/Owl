#ifndef OWL_GAME
#define OWL_GAME

namespace owl
{
	class Game
	{
	public:
		Game() {};

		virtual void OWL_API OnStart() = 0;
		virtual void OWL_API OnUpdate() = 0;
		virtual void OWL_API OnDraw() = 0;
		virtual void OWL_API OnFinalize() = 0;
	};
}

#endif // !OWL_GAME
