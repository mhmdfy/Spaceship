
// The window that the game will appear in.  Encapsulates the DirectX implementation details, so we 
//	don't have to worry about them.

#pragma once

#include "GPShip.h"
#include "GPRock.h"
#include "GPBullet.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
using namespace std;

class GPGameWindow
{
public:
	GPGameWindow();
	virtual ~GPGameWindow();

	// Initializes the game.  Returns false if initialization fails.
	// ARGUMENTS:
	//	hInstance - the window instance passed in to WinMain()
	//	cmdLine - the commandline arguments passed in to WinMain()
	//	nCmdShow - I'm not sure, to be honest - also passed in to WinMain
	bool					Init(HINSTANCE hInstance, const char* cmdLine, int nCmdShow);

	// Called every frame.  Returns true if the game should keep running, false if it's time to exit.
	void					Update();

	//font functions
	LPD3DXFONT				MakeFont(string name, int size);
	void					FontPrint(LPD3DXFONT font, int x, int y, string text, D3DCOLOR color = D3DCOLOR_XRGB(255,255,255));

private:
	// an Update() helper that handles the input and manipulates the image accordingly
	void					HandleInput();

	// An Update() helper that draws the image.
	void					Draw();

private:
	// the path and name of our background image
	const char*				m_BackgroundFile;

	// the window object that we're managing
	HWND					m_Window;

	//Direct3D objects
	LPDIRECT3D9				m_d3d; 
	LPDIRECT3DDEVICE9		m_d3ddev; 
	LPDIRECT3DSURFACE9		m_Backbuffer;
	LPDIRECT3DSURFACE9		m_Surface;
	LPD3DXSPRITE			m_spriteobj;

	//used for scaling and shifting the bitmap
	RECT					m_Rectangle;

private:
	// DELIBERATELY UNDEFINED
	GPGameWindow(const GPGameWindow& rhs);
	GPGameWindow&			operator=(const GPGameWindow& rhs);
	bool					operator==(const GPGameWindow& rhs);
	bool					operator<(const GPGameWindow& rhs);

private:
	GPShip m_ship;
	int numOfRocks;
	int rockCount;
	GPRock  m_rock;
	std::vector<GPRock> m_rocks;
	GPBullet m_bullet;
	std::vector<GPBullet> m_bullets;

	bool paused;
};

