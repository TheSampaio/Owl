#ifndef OWL_INPUT_H
#define OWL_INPUT_H

class Input
{
public:
	Input();
	~Input();

	// Main methods
	bool GetKeyTaped(int KeyCode);

	inline bool GetKeyPressed(int KeyCode) { return s_Keys[KeyCode]; }
	inline bool GetKeyReleased(int KeyCode) { return !s_Keys[KeyCode]; }
	inline std::array<int, 2> GetMousePosition() { return s_MousePosition; }

	// Static methods
	static LRESULT CALLBACK Procedure(HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam);


private:
	// Static attributes
	static bool s_Flags[256];
	static bool s_Keys[256];

	static short s_MouseWheel;
	static std::array<int, 2> s_MousePosition;

};

#endif // !OWL_INPUT_H
