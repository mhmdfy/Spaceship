
#include "GPSprites.h"

GPSprites::GPSprites()
{
	m_Surface = NULL;
	m_comps = GPSpriteComponents();
	m_image = NULL;
}

GPSprites::~GPSprites(){}

bool GPSprites::Init(HINSTANCE& hInstance, const char* cmdLine, int nCmdShow, LPDIRECT3DDEVICE9& d3ddev, int image_width, int image_height){
    //create m_Surface
    HRESULT result = d3ddev->CreateOffscreenPlainSurface(
        image_width,			//width of the m_Surface
        image_height,			//height of the m_Surface
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
        m_image,				//source filename
        NULL,					//source rectangle
        D3DX_DEFAULT,			//controls how image is filtered
        0,						//for transparency (0 for none)
        NULL);					//source image info (usually NULL)

    //make sure file was loaded okay
    if (!SUCCEEDED(result)) 
		return false;

    return true;
}

void GPSprites::create(float x, float y, int width, int height, float xVelocity, float yVelocity, char* image)
{
	m_comps.setX(x);
	m_comps.setY(y);
	m_comps.setWidth(width);
	m_comps.setHeight(height); 
	m_comps.setXVelocity(xVelocity);
	m_comps.setYVelocity(yVelocity);
	m_image = image;

	RECT display = {(long)0, (long)0, (long)m_comps.getWidth(), (long)m_comps.getHeight()};
	m_display = display;
}

void GPSprites::Update()
{
	if(inBound())
		m_comps.move();
}

GPSpriteComponents& GPSprites::getInfo()
{
	return m_comps;
}

bool GPSprites::inBound()
{
	if(m_comps.getX() >= 0 && m_comps.getX()+m_comps.getWidth() <= 1024
		&& m_comps.getY() >= 0 && m_comps.getY()+m_comps.getHeight() <= 768)
		return true;

	return false;
}

int GPSprites::getSign(float x)
{
	if (x < 0 )
		return -1;
	else
		return 1;
}

bool GPSprites::collide(GPSprites other)
{
	if(m_comps.getDistance(other.getInfo()) <= ((m_comps.getWidth() + other.getInfo().getWidth())/2))
	{
		return true;
	}
	return false;
}


bool GPSprites::draw(LPDIRECT3DSURFACE9& Backbuffer, LPDIRECT3DDEVICE9& d3ddev)
{
	D3DSURFACE_DESC desc;
	m_Surface->GetDesc(&desc);

	RECT dest_rect = {(long)m_comps.getX(), (long)m_comps.getY(), (long)m_comps.getX() + m_comps.getWidth(), (long)m_comps.getY() + m_comps.getHeight()};

	d3ddev->StretchRect(m_Surface, &m_display, Backbuffer, &dest_rect, D3DTEXF_NONE);
	return true;
}
