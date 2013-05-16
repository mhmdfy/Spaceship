
// The game manager - a singleton that contains the entire game.

#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class GPGameWindow;

class GPGameManager
{
private:
	GPGameManager();
	virtual ~GPGameManager();

public:
	static GPGameManager&		Get();

	// Initializes the game.  Returns false if initialization fails.
	// ARGUMENTS:
	//	hInstance - the window instance passed in to WinMain()
	//	cmdLine - the commandline arguments passed in to WinMain()
	//	nCmdShow - I'm not sure, to be honest - also passed in to WinMain
	bool						Init(HINSTANCE hInstance, const char* cmdLine, int nCmdShow);
	void						Clear();

	// Called every frame.  Returns true if the game should keep running, false if it's time to exit.
	void						Update();

	// Used to keep track of whether it's time to exit the game.
	void						SetGameOver()							{ m_bIsGameOver = true; }
	bool						IsGameOver() const						{ return m_bIsGameOver; }

private:
	// Storage for our singleton game manager
	static GPGameManager*		ms_pGameManager;

	// The main game window
	GPGameWindow*				m_pGameWindow;

	// Keeps track of whether the game is over.
	bool						m_bIsGameOver;

private:
	// DELIBERATELY UNDEFINED
	GPGameManager(const GPGameManager& rhs);
	GPGameManager&				operator=(const GPGameManager& rhs);
	bool						operator==(const GPGameManager& rhs);
	bool						operator<(const GPGameManager& rhs);

};

