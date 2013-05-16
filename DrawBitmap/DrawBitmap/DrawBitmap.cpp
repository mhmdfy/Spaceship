/*
	Based on the:
    Beginning Game Programming, Third Edition
    Chapter 4
    Load Bitmap program

	Enhanced by Martha Hamlin
	Further enhanced by Kevin Dill
*/

#include "GPGameManager.h"

/**
 ** Windows entry point function
 **/
// LPCMDLINE to input string
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GPGameManager& gameMgr = GPGameManager::Get();

	if (!gameMgr.Init(hInstance, lpCmdLine, nCmdShow))
		return 0;

    // main message loop
	MSG message;
	while (!gameMgr.IsGameOver())
    {
		// Handle any windows messages
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) 
	    {
		    TranslateMessage(&message);
		    DispatchMessage(&message);
	    }

        // Update the game
        gameMgr.Update();
    }

	gameMgr.Clear();

	return message.wParam;
}
