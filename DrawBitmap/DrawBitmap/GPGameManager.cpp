
// The main game object, which contains the entire game.

#include "GPGameManager.h"
#include "GPSprites.h"
#include "GPGameWindow.h"

GPGameManager* GPGameManager::ms_pGameManager = NULL;

GPGameManager::GPGameManager()
: m_pGameWindow(new GPGameWindow)
, m_bIsGameOver(false)
{
}

GPGameManager::~GPGameManager()
{
	delete m_pGameWindow;
}

GPGameManager& GPGameManager::Get()
{
	if (!ms_pGameManager)
		ms_pGameManager = new GPGameManager;
	return *ms_pGameManager;
}

bool GPGameManager::Init(HINSTANCE hInstance, const char* cmdLine, int nCmdShow)
{
	bool bSuccess = true;

	bSuccess = bSuccess && m_pGameWindow->Init(hInstance, cmdLine, nCmdShow);

	return bSuccess;
}

void GPGameManager::Clear()
{
	delete ms_pGameManager;
	ms_pGameManager = NULL;
}


void GPGameManager::Update()
{
	m_pGameWindow->Update();
}

