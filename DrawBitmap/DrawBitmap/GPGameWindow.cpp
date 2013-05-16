
#include "GPGameWindow.h"

#include "GPGameManager.h"

// configuration constants
const char* kApplicationTitle = "Load Bitmap Program";
const int kScreenWidth = 1024;
const int kScreenHeight = 768;

// black magic that tells me if a particular key is down
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

GPGameWindow::GPGameWindow()
: m_BackgroundFile("ProgrammerArt.bmp")
// , m_Window
, m_d3d(NULL)
, m_d3ddev(NULL)
, m_Backbuffer(NULL)
, m_Surface(NULL)
{
	m_Rectangle.left = 0;
	m_Rectangle.top = 0;
	m_Rectangle.right = kScreenWidth;
	m_Rectangle.bottom = kScreenHeight;
	//sprites creation
	m_ship.spawn();
	numOfRocks = 3;
	rockCount = 0;
	m_rock.spawn();
	m_bullet.spawn(0,0);
	paused = false;
}

GPGameWindow::~GPGameWindow()
{
	if (m_d3d)
		m_d3d->Release();

	if (m_d3ddev)
		m_d3ddev->Release();

	if (m_Backbuffer)
		m_Backbuffer->Release();

	if (m_Surface)
		m_Surface->Release();
}

/**
 ** Windows event handling function
 **/
LRESULT WINAPI WinProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            GPGameManager::Get().SetGameOver();
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc( hWnd, msg, wParam, lParam );
}

bool GPGameWindow::Init(HINSTANCE hInstance, const char* cmdLine, int nCmdShow)
{

	//initialize window settings
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX); 
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = (WNDPROC)WinProc;
    wc.cbClsExtra	 = 0;
    wc.cbWndExtra	 = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = NULL;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = kApplicationTitle;
    wc.hIconSm       = NULL;
    RegisterClassEx(&wc);

	//create a new window
    m_Window = CreateWindow(kApplicationTitle, kApplicationTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 
							CW_USEDEFAULT, kScreenWidth, kScreenHeight, NULL, NULL, hInstance, NULL);

    //was there an error creating the window?
    if (!m_Window) 
		return false;

    //display the window
    ShowWindow(m_Window, nCmdShow);
    UpdateWindow(m_Window);			// TODO: should I call this every update?  The name certainly suggests that...

	//initialize Direct3D
    m_d3d = Direct3DCreate9(D3D_SDK_VERSION);
    if (!m_d3d)
    {
        MessageBox(m_Window, "Error initializing Direct3D", "Error", MB_OK);
        return false;
    }

    //set Direct3D presentation parameters
    D3DPRESENT_PARAMETERS d3dpp; 
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.BackBufferCount = 1;
    d3dpp.BackBufferWidth = kScreenWidth;
    d3dpp.BackBufferHeight = kScreenHeight;
    d3dpp.hDeviceWindow = m_Window;

    //create Direct3D device
    m_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_Window,
						D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_d3ddev);

    if (!m_d3ddev)
    {
        MessageBox(m_Window, "Error creating Direct3D device", "Error", MB_OK);
        return 0;
    }

    //clear the m_Backbuffer to black
    m_d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);
    
    //create m_Surface
    HRESULT result = m_d3ddev->CreateOffscreenPlainSurface(
        kScreenWidth,			//width of the m_Surface
        kScreenHeight,			//height of the m_Surface
        D3DFMT_X8R8G8B8,		//m_Surface format
        D3DPOOL_DEFAULT,		//memory pool to use
        &m_Surface,				//pointer to the m_Surface
        NULL);					//reserved (always NULL)

    if (!SUCCEEDED(result)) 
		return false;

    //load m_Surface from file into newly created m_Surface
    result = D3DXLoadSurfaceFromFile(
        m_Surface,				//destination m_Surface
        NULL,					//destination palette
        NULL,					//destination rectangle
        m_BackgroundFile,		//source filename
        NULL,					//source rectangle
        D3DX_DEFAULT,			//controls how image is filtered
        0,						//for transparency (0 for none)
        NULL);					//source image info (usually NULL)

    //make sure file was loaded okay
    if (!SUCCEEDED(result)) 
		return false;

	//create sprite object
    D3DXCreateSprite(m_d3ddev, &m_spriteobj);

	//initializeing the sprites
	if(!m_ship.Init(hInstance, cmdLine, nCmdShow, m_d3ddev, 90, 86))
		{
			MessageBox(m_Window, "Error creating spaceship sprite", "Error", MB_OK);
			return false;
		}

	if(!m_rock.Init(hInstance, cmdLine, nCmdShow, m_d3ddev, 360, 86))
	{
		MessageBox(m_Window, "Error creating rock sprite", "Error", MB_OK);
		return false;
	}

	for(int i = 0; i < numOfRocks ; i++)
	{
		m_rocks.push_back(m_rock);
	}

	if(!m_bullet.Init(hInstance, cmdLine, nCmdShow, m_d3ddev, 25, 6))
	{
		MessageBox(m_Window, "Error creating bullet sprite", "Error", MB_OK);
		return false;
	}

    return true;
}

void GPGameWindow::Update()
{
	HandleInput();
	Draw();

	if(paused)
		return;

	//sprites update
	m_ship.Update();
	for(int i = 0; i < m_rocks.size(); i++)
	{
		m_rocks[i].Update();
		if(m_ship.collide(m_rocks[i]))
		{
			MessageBox(m_Window, "You were destroyed by a rock!", "GAME END", MB_OK);
			PostMessage(m_Window, WM_DESTROY, 0, 0);
		}

		for(int j = 0; j < m_bullets.size(); j++)
		{
			if(m_rocks[i].collide(m_bullets[j]))
			{
				m_rocks.erase(m_rocks.begin()+i);
				numOfRocks--;
				break;
			}
		}
	}

	rockCount++;
	if(rockCount == 100)
	{
		numOfRocks++;
		m_rocks.push_back(m_rock);
		rockCount = 0;
	}

	if(numOfRocks == 0)
	{
		MessageBox(m_Window, "YAY! you won!", "GAME END", MB_OK);
		PostMessage(m_Window, WM_DESTROY, 0, 0);
	}

	for(int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i].Update();
		if(!m_bullets[i].inBound())
			m_bullets.erase(m_bullets.begin()+i);
	}
}

// an Update() helper that handles the input and manipulates the image accordingly
void GPGameWindow::HandleInput()
{
	//check for escape key (to exit program)
    if (KEY_DOWN(VK_ESCAPE))
        PostMessage(m_Window, WM_DESTROY, 0, 0);

	//W or UpArrow move up
	if (KEY_DOWN(VK_UP) || KEY_DOWN(0x57))
	{
		m_ship.moveUp();
	}

	//S or DownArrow move down
	if (KEY_DOWN(VK_DOWN) || KEY_DOWN(0x53))
	{
		m_ship.moveDown();
	}

	//A or LeftArrow move left
	if (KEY_DOWN(VK_LEFT) || KEY_DOWN(0x41))
	{
		m_ship.moveLeft();
	}

	//D or RightArrow move right
	if (KEY_DOWN(VK_RIGHT) || KEY_DOWN(0x44))
	{
		m_ship.moveRight();
	}

	//spacebar to shoot a bullet
	if(KEY_DOWN(0x20))
	{
		int x = m_ship.getInfo().getX() + (m_ship.getInfo().getWidth()/2);
		int y = m_ship.getInfo().getY() + (m_ship.getInfo().getHeight()/2);
		m_bullet.spawn(x, y);
		m_bullets.push_back(m_bullet);
	}

	// pause the game with p
	if(KEY_DOWN(0x50))
	{
		if(paused)
			paused = false;
		else
			paused = true;
	}
}

// An Update() helper that draws the image.
void GPGameWindow::Draw()
{
    //make sure the Direct3D device is valid
    if (!m_d3ddev) return;
	
	//create pointer to the back buffer
    m_d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_Backbuffer);

	FontPrint( MakeFont("Arial",24), 500, 540, "Number of rocks: " + numOfRocks);

    //start rendering
    if (m_d3ddev->BeginScene())
    {
        //draw m_Surface to the m_Backbuffer
		// Using m_pSrcRect, which handles shifting and scaling 
		m_d3ddev->StretchRect(m_Surface, &m_Rectangle, m_Backbuffer, NULL, D3DTEXF_NONE);

		//draw the sprites
		m_ship.draw(m_Backbuffer, m_d3ddev);

		for(int i=0; i< m_rocks.size() ; i++)
			m_rocks[i].draw(m_Backbuffer, m_d3ddev);

		for(int i=0; i<m_bullets.size() ; i++)
			m_bullets[i].draw(m_Backbuffer, m_d3ddev);

        //stop rendering
        m_d3ddev->EndScene();
        m_d3ddev->Present(NULL, NULL, NULL, NULL);
    }
}

LPD3DXFONT GPGameWindow::MakeFont(string name, int size)
{
    LPD3DXFONT font = NULL;

    D3DXFONT_DESC desc = {
        size,                   //height
        0,                      //width
        0,                      //weight
        0,                      //miplevels
        false,                  //italic
        DEFAULT_CHARSET,        //charset
        OUT_TT_PRECIS,          //output precision
        CLIP_DEFAULT_PRECIS,    //quality
        DEFAULT_PITCH,          //pitch and family
        ""                      //font name
    };

    strcpy(desc.FaceName, name.c_str());

    D3DXCreateFontIndirect(m_d3ddev, &desc, &font);

    return font;
}

void GPGameWindow::FontPrint(LPD3DXFONT font, int x, int y, string text, D3DCOLOR color)
{
    //figure out the text boundary
    RECT rect = { x, y, 0, 0 };
    font->DrawText( NULL, text.c_str(), text.length(), &rect, DT_CALCRECT, color); 

    //print the text
    font->DrawText(m_spriteobj, text.c_str(), text.length(), &rect, DT_LEFT, color); 
}

