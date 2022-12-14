#pragma once

class Input
{
public:
	Input() {};

	// Main methods
	bool GetKeyTaped(int KeyCode);	

	inline bool GetKeyPressed(int KeyCode)        const { return s_bKeys[KeyCode]; }
	inline bool GetKeyReleased(int KeyCode)       const { return !s_bKeys[KeyCode]; }
	inline std::array<int, 2>& GetMousePosition() const { return s_MousePosition; }
	inline short& GetMouseWheel()                 const { return s_MouseWheel; }

	// Static methods
	static LRESULT CALLBACK Procedure(HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam);


private:
	// Static attributes
	static bool s_bFlags[256];
	static bool s_bKeys[256];

	static short s_MouseWheel;
	static std::array<int, 2> s_MousePosition;

};
