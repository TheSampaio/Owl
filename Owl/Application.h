#ifndef OWL_APPLICATION_H
#define OWL_APPLICATION_H

#include "PCH.h"
#include "Window.h"

class CApplication
{
public:
	CApplication();
	~CApplication();

	// Main methods
	int Start();

	// Get methods
	CWindow*& GetWindow();

private:
	int Update();

	static CWindow* s_Window;
};

#endif // !OWL_APPLICATION_H
