#include "dxGraphics.h"

#define TILEWIDTH 64
#define TILEHEIGHT 64
#define MAPWIDTH 25
#define MAPHEIGHT 18
#define GAMEWORLDWIDTH (TILEWIDTH * MAPWIDTH)
#define GAMEWORLDHEIGHT (TILEHEIGHT * MAPHEIGHT)

LPDIRECT3D9 d3d = NULL;
LPDIRECT3DDEVICE9 d3ddev = NULL;
LPDIRECT3DSURFACE9 backBuffer = NULL;
LPDIRECT3DSURFACE9 frontBuffer = NULL;
RECT screenresolution;
HWND hWnd;
D3DPRESENT_PARAMETERS d3dpp;
LPD3DXSPRITE sprite_handler;
int ScrollX, ScrollY; //current scroll position
int SpeedX, SpeedY;

int MAPDATA[MAPWIDTH*MAPHEIGHT] = {
	80, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
	81, 81, 81, 82, 90, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 92, 3, 3, 3, 3, 3, 92, 3,
	92, 90, 3, 13, 83, 96, 3, 3, 23, 3, 92, 3, 13, 92, 3, 3, 3, 3, 3, 3, 11, 3, 13, 3, 3, 92,
	90, 3, 3, 3, 3, 3, 3, 3, 10, 3, 3, 3, 3, 3, 23, 3, 3, 3, 3, 3, 3, 3, 13, 3, 92, 90, 3, 96,
	3, 13, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 96, 3, 23, 3, 96, 3, 3, 92, 90, 3, 3, 3, 3, 3, 3,
	13, 3, 3, 3, 13, 3, 3, 11, 3, 3, 3, 3, 3, 3, 3, 13, 3, 92, 90, 3, 83, 11, 3, 92, 3, 3, 3,
	3, 3, 11, 3, 3, 3, 3, 3, 3, 3, 83, 3, 3, 3, 92, 92, 90, 3, 3, 3, 96, 3, 13, 3, 3, 3, 11,
	10, 3, 3, 3, 3, 3, 13, 3, 3, 13, 3, 3, 3, 92, 90, 3, 23, 3, 3, 3, 3, 3, 3, 96, 3, 3, 83,
	3, 3, 3, 92, 3, 3, 3, 3, 3, 13, 3, 92, 90, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 23, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 92, 90, 3, 3, 3, 11, 3, 92, 3, 3, 13, 3, 3, 131, 3, 10, 3, 3, 3, 96,
	3, 92, 3, 96, 3, 92, 90, 3, 13, 83, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 13, 3, 3, 3, 3, 3, 3,
	3, 3, 92, 90, 3, 3, 3, 3, 13, 3, 3, 3, 3, 3, 11, 96, 3, 3, 3, 3, 3, 3, 13, 3, 13, 3, 11,
	92, 90, 92, 3, 13, 3, 3, 3, 3, 3, 3, 92, 3, 10, 3, 23, 3, 3, 3, 3, 3, 3, 3, 3, 3, 92, 90,
	3, 3, 3, 3, 3, 96, 3, 23, 3, 3, 3, 3, 3, 3, 3, 3, 83, 3, 3, 13, 3, 96, 3, 92, 90, 3, 3, 3,
	3, 92, 3, 3, 3, 3, 3, 13, 3, 3, 3, 13, 3, 3, 3, 11, 3, 3, 3, 3, 92, 90, 3, 13, 3, 3, 3, 3,
	3, 3, 3, 96, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 92, 3, 3, 92, 100, 101, 101, 101, 101, 101,
	101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101,
	101, 101, 102
};

bool Init_Graphics(HWND hwnd, bool fs)//Constructor
{
	GetClientRect(hwnd, &screenresolution);
	hWnd = hwnd;

	//initialize Direct3D
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d == NULL)
	{
		MessageBox(hWnd, "Error initializing Direct3D", "Constructor error", MB_OK);
		return 0;
	}
	SetMode(screenresolution.right, screenresolution.bottom, fs);
	return 1;
}

bool SetMode(int x, int y, bool fs){
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = !fs;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = x;
	d3dpp.BackBufferHeight = y;

	//create Direct3D device
	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	if (d3ddev == NULL)
	{
		MessageBox(hWnd, "Error creating Direct3D device", "Error", MB_OK);
		return 0;
	}
	//clear the backbuffer to black
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	//create pointer to the back buffer
	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
	//return okay
	return 1;
}

RECT GetMode(){
	return screenresolution;
}

void Clear(DWORD color)
{
	int a, r, g, b;
	r = color >> 16 & 0xff;
	g = color >> 8 & 0xff;
	b = color & 0xff;

	//make sure the Direct3D device is valid
	if (d3ddev == NULL)
		return;
	//set backbuffer to specified color
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(r, g, b), 1.0f, 0);
	//paint
	if (d3ddev->BeginScene())
	{
		d3ddev->EndScene();
	}

	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void DrawImage(char const* pathInParam, int x, int y, float scale){
	RECT pos;//Position rect
	LPDIRECT3DSURFACE9 img;
	D3DXIMAGE_INFO img_info;
	D3DXGetImageInfoFromFile(pathInParam, &img_info);
	int width = img_info.Width * scale;
	int height = img_info.Height * scale;//desired scaled size

	img = LoadSurface(pathInParam);

	//make sure the Direct3D device is valid
	if (d3ddev == NULL)
	{
		MessageBox(hWnd, "Error creating Direct3D device","DrawImage Error", MB_OK);
		return;
	}

	pos.left = x;
	pos.top = y;
	pos.right = width; //* drawThis.getScale();//Width and height is scaled according to image obj properties
	pos.bottom = height; //* drawThis.getScale();

	//start rendering
	if (d3ddev->BeginScene())//<Tells Direct3D we are about to paint, locks up VRAM
	{//Now we can use VRAM data>
		d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);//create pointer to the back buffer
		d3ddev->StretchRect(img, NULL, backBuffer, &pos, D3DTEXF_NONE);	//draw surface to the backbuffer
		d3ddev->EndScene();//stop rendering, unlock VRAM
	}
	d3ddev->Present(NULL, NULL, NULL, NULL);//display the back buffer on the screen (nullparameters are bout swapchains and window handling)
}

void DrawText(char const* text, int textSize, int x, int y, DWORD color){
	HRESULT result;
	HDC hdc = GetDC(0); // hämta skärmens DC
	int logicalHeight = -MulDiv(textSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);

	LPD3DXFONT font;

	int a, r, g, b;
	a = color >> 24 & 0xff;
	r = color >> 16 & 0xff;
	g = color >> 8 & 0xff;
	b = color & 0xff;

	result = D3DXCreateFont(
		d3ddev,
		logicalHeight,
		0, // bredden för fonten, eller 0 för att låta Windows bestämma
		0, // ”vikt”, till exempel fet stil
		1, // mip-nivåer
		0, // 1 = kursiv stil
		ANSI_CHARSET,
		OUT_TT_ONLY_PRECIS, // använd endast true-type fonter
		0, // ”kvalité”, används ej för true-type
		0, // ?
		"Times New Roman", // fontnamnet
		&font);

	RECT rect = { x, y, 0, 0 };//<-startpunkt

	//start rendering
	if (d3ddev->BeginScene())//<Tells Direct3D we are about to paint, locks up VRAM
	{//Now we can use VRAM data>
		font->DrawText(
			0,
			text,
			-1,
			&rect,
			DT_NOCLIP,
			D3DCOLOR_ARGB(a, r, g, b));
		d3ddev->EndScene();//stop rendering, unlock VRAM
	}
	d3ddev->Present(NULL, NULL, NULL, NULL);//display the back buffer on the screen (nullparameters are bout swapchains and window handling)

}

void DrawTile(LPDIRECT3DSURFACE9 source, // source surface image
	int tilenum, // tile #
	int width, // tile width
	int height, // tile height
	int columns, // columns of tiles
	LPDIRECT3DSURFACE9 dest, // destination surface
	int destx, // destination x
	int desty) // destination y
{
	//create a RECT to describe the source image
	RECT r1;
	r1.left = (tilenum % columns) * width;
	r1.top = (tilenum / columns) * height;
	r1.right = r1.left + width;
	r1.bottom = r1.top + height;
	//set destination rect
	RECT r2 = { destx, desty, destx + width, desty + height };
	//draw the tile
	d3ddev->StretchRect(source, &r1, dest, &r2, D3DTEXF_NONE);
}

void DrawSpriteObject(LPDIRECT3DTEXTURE9 tx, Sprite obj){

	HRESULT rs = D3DXCreateSprite(d3ddev, &sprite_handler);
	sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXVECTOR3 pos = obj.getPosition();
	sprite_handler->Draw(
		tx,
		NULL,
		NULL,
		&pos,
		D3DCOLOR_XRGB(255, 255, 255));
	sprite_handler->End();
	//stop rendering
}

///*
//This function draws a sprite.
//Sprite creation works this way:
//*create a sprite and load a bitmap into the sprite surface.
//*control the animation of the sprite.
//*move the sprite on the screen.
//These should be supported by the class SpriteState.
//121*/
//void DrawSprite(LPDIRECT3DTEXTURE9 sprite[], int x, int y, int currentframe, LPDIRECT3DSURFACE9 back){
//	//start rendering
//	if (d3ddev->BeginScene())
//	{
//		d3ddev->StretchRect(back, NULL, backBuffer, NULL, D3DTEXF_NONE);
//		//start sprite handler
//		sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);
//
//		//create vector to update sprite position
//		D3DXVECTOR3 position(x, y, 0);
//
//		//draw the sprite
//		sprite_handler->Draw(
//			sprite[currentframe],
//			NULL,
//			NULL,
//			&position,
//			D3DCOLOR_XRGB(255, 255, 255));
//
//		//stop drawing
//		sprite_handler->End();
//
//		//stop rendering
//		d3ddev->EndScene();
//	}
//	//display the back buffer on the screen
//	d3ddev->Present(NULL, NULL, NULL, NULL);
//}
//
//void DrawSprites(LPDIRECT3DTEXTURE9 sprite_array[], Sprite sprite_info[], int sprites, int currentframe, LPDIRECT3DSURFACE9 back){
//	//start rendering
//	if (d3ddev->BeginScene())
//	{
//		d3ddev->StretchRect(back, NULL, backBuffer, NULL, D3DTEXF_NONE);
//		//start sprite handler
//		sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);
//		int n;
//		D3DXVECTOR3 position(0, 0, 0); //ball position vector
//		//draw the balls
//		for (n = 0; n<sprites; n++)
//		{
//			position.x = (float)sprite_info[n].getPosX();
//			position.y = (float)sprite_info[n].getPosY();
//			sprite_handler->Draw(
//				sprite_array[currentframe],
//				NULL,
//				NULL,
//				&position,
//				D3DCOLOR_XRGB(255, 255, 255));
//		}
//
//		//stop drawing
//		sprite_handler->End();
//
//		//stop rendering
//		d3ddev->EndScene();
//	}
//	//display the back buffer on the screen
//	d3ddev->Present(NULL, NULL, NULL, NULL);
//}
//
/*
Load surface
Requires parameters:
int Width, Height
char const* Path
*/
LPDIRECT3DSURFACE9 LoadSurface(char const* pathInParam, D3DCOLOR transcolor)
{
	LPDIRECT3DSURFACE9 image = NULL;
	D3DXIMAGE_INFO info;
	HRESULT result;
	result = D3DXGetImageInfoFromFile(pathInParam, &info);
	if (result != D3D_OK)
		return NULL;

	//prep surface for delivery
	result = d3ddev->CreateOffscreenPlainSurface(
		info.Width,
		info.Height,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&image,
		NULL);

	if (result != D3D_OK)
		return NULL;

	//load picture into surface
	result = D3DXLoadSurfaceFromFile(
		image,
		NULL,
		NULL,
		pathInParam,//loads the picture from path
		NULL,
		D3DX_DEFAULT,
		transcolor,
		NULL);

	//make sure file was loaded okay
	if (result != D3D_OK)
		return NULL;

	return image;
}

LPDIRECT3DTEXTURE9 LoadTexture(char *filename, D3DCOLOR transcolor){
	LPDIRECT3DTEXTURE9 texture = NULL;//Texture for foreground objects

	//the struct for reading bitmap file info
	D3DXIMAGE_INFO info;

	//standard Windows return value
	HRESULT result;

	//get width and height from bitmap file
	result = D3DXGetImageInfoFromFile(filename, &info);
	if (result != D3D_OK)
		return NULL;

	//create the new texture by loading a bitmap image file
	D3DXCreateTextureFromFileEx(
		d3ddev,              //Direct3D device object
		filename,            //bitmap filename
		info.Width,          //bitmap image width
		info.Height,         //bitmap image height
		1,                   //mip-map levels (1 for no chain)
		D3DPOOL_DEFAULT,     //the type of surface (standard)
		D3DFMT_UNKNOWN,      //surface format (default)
		D3DPOOL_DEFAULT,     //memory class for the texture
		D3DX_DEFAULT,        //image filter
		D3DX_DEFAULT,        //mip filter
		transcolor,          //color key for transparency
		&info,               //bitmap file info (from loaded file)
		NULL,                //color palette
		&texture);          //destination texture

	//make sure the bitmap textre was loaded correctly
	if (result != D3D_OK)
		return NULL;

	return texture;
}

/*
This is the "camera" of the gameworld map. It scrolls the screen
depending on the screen width.
*/
void ScrollScreen()
{
	int SCREEN_WIDTH = screenresolution.right;
	int SCREEN_HEIGHT = screenresolution.bottom;

	//update horizontal scrolling position and speed
	ScrollX += SpeedX;
	if (ScrollX < 0)
	{
		ScrollX = 0;
		SpeedX = 0;
	}
	else if (ScrollX > GAMEWORLDWIDTH - SCREEN_WIDTH)
	{
		ScrollX = GAMEWORLDWIDTH - SCREEN_WIDTH;
		SpeedX = 0;
	}

	//update vertical scrolling position and speed
	ScrollY += SpeedY;
	if (ScrollY < 0)
	{
		ScrollY = 0;
		SpeedY = 0;
	}
	else if (ScrollY > GAMEWORLDHEIGHT - SCREEN_HEIGHT)
	{
		ScrollY = GAMEWORLDHEIGHT - SCREEN_HEIGHT;
		SpeedY = 0;
	}

	//set dimensions of the source image
	RECT r1 = { ScrollX, ScrollY, ScrollX + SCREEN_WIDTH - 1,
		ScrollY + SCREEN_HEIGHT - 1 };
	//set the destination rect
	RECT r2 = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };
	//draw the current game world view
	d3ddev->StretchRect(frontBuffer, &r1, backBuffer, &r2,
		D3DTEXF_NONE);
}
/*
Sprite setup
Transparency color is pink.
*/
//bool Sprite_setup(LPDIRECT3DTEXTURE9 sprite_array[], char const *filename, int arraySize){
//	char s[20];
//	int n;
//
//	//create sprite handler object
//	HRESULT result = D3DXCreateSprite(d3ddev, &sprite_handler);
//	if (result != D3D_OK)
//		return 0;
//
//	//load the sprite animation
//	for (n = 0; n<arraySize; n++)
//	{
//		//printf("%d", sizeof(sprite_array + 1));
//		//set up the filename
//		//sprintf(s, "cat%d.bmp", n + 1);
//		sprintf_s(s, "%s%d.bmp", filename, n + 1);
//		//load texture with "pink" as the transparent color
//		sprite_array[n] = LoadTexture(s, D3DCOLOR_XRGB(255, 0, 255));
//		if (sprite_array[n] == NULL){
//			MessageBox(hWnd, "Sprite setup failed.", "Array sprite error", MB_OK);
//			return 0;
//		}
//	}
//	return 1;
//}
//
void createMapTiles()
{
	HRESULT result;
	int x, y;
	LPDIRECT3DSURFACE9 tiles;
	//load the bitmap image containing all the tiles
	tiles = LoadSurface("groundtiles.bmp", D3DCOLOR_XRGB(0, 0, 0));
	//create the scrolling game world bitmap
	result = d3ddev->CreateOffscreenPlainSurface(
		GAMEWORLDWIDTH, //width of the surface
		GAMEWORLDHEIGHT, //height of the surface
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&frontBuffer, //pointer to the surface
		NULL);
	if (result != D3D_OK)
	{
		MessageBox(NULL, "Error creating working surface!", "Error", 0);
		return;
	}
	//fill the gameworld bitmap with tiles dvs chop the bmp op
	for (y = 0; y < MAPHEIGHT; y++)
		for (x = 0; x < MAPWIDTH; x++)
			DrawTile(tiles, MAPDATA[y * MAPWIDTH + x], 64, 64, 16,//function is located in dxGraphics
			frontBuffer, x * 64, y * 64);
	//now the tiles bitmap is no longer needed
	tiles->Release();
}

void Kill_Graphics(){
	d3d->Release();
	if (frontBuffer != NULL){
		frontBuffer->Release();
	}
	d3ddev->Release();
	if (sprite_handler != NULL){
		sprite_handler->Release();
	}
	if (backBuffer != NULL){
		backBuffer->Release();
	}
}

void renderTiles(LPDIRECT3DTEXTURE9 tx, Sprite sp){
	//start rendering
	if (d3ddev->BeginScene())
	{
		//update the scrolling view
		ScrollScreen();
		DrawSpriteObject(tx,sp);
		d3ddev->EndScene();
	}
	//display the back buffer on the screen
	d3ddev->Present(NULL, NULL, NULL, NULL);
}

int getScrollX(){
	return ScrollX;
}

int getScrollY(){
	return ScrollY;
}

void setScrollX(int x){
	ScrollX = x;
}

void setScrollY(int y){
	ScrollY = y;
}

LPDIRECT3DDEVICE9 getDirect3dDevice(){
	return d3ddev;
}