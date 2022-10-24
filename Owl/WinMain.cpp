#include "PCH.h"
#include "Application.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdLine, _In_ INT nCmdShow)
{
	CApplication Application;
	Application.GetWindow()->SetSize(1024, 720);
	Application.GetWindow()->SetTitle("Super Game");
	Application.GetWindow()->SetBackgroundColor(255, 253, 186);	

	int State = Application.Start();
	return State;
}