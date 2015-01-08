#ifndef _DX_GRAPHICS_H
#define _DX_GRAPHICS_H

#include <d3d9.h>
#include <d3dx9.h>
#include "dxSprite.h"



bool Init_Graphics(HWND, bool fullscreen = false);
bool SetMode(int, int, bool); // sets resolution, width*height, fullscreen.	
RECT GetMode();
void Flip(bool); // switch sceen / backbuffer. D3DPresent vertical retrace.
void Clear(DWORD color = 0); // Clears backbuffer to spec color (black default).
void DrawImage(char const*, int x = 0, int y = 0, float = 1.0);
void DrawText(char const*, int, int, int, DWORD); //Draw text at x,y, size.
void DrawTile(LPDIRECT3DSURFACE9, int, int, int, int, LPDIRECT3DSURFACE9, int, int);
void DrawSpriteObject(LPDIRECT3DTEXTURE9, Sprite);
void DrawSprite(LPDIRECT3DTEXTURE9 sprite_array[], int x, int y, int currentframe, LPDIRECT3DSURFACE9 back);
void DrawSprites(LPDIRECT3DTEXTURE9 sprite_array[], Sprite sprite_info[], int sprites, int currentframe, LPDIRECT3DSURFACE9 back);
LPDIRECT3DSURFACE9 LoadSurface(char const* pathInParam, D3DCOLOR transcolor = (255, 0, 255));
LPDIRECT3DTEXTURE9 LoadTexture(char *filename, D3DCOLOR transcolor = (255, 0, 255));
bool Sprite_setup(LPDIRECT3DTEXTURE9 sprite_array[], char const *filename, int arraySize);
void ScrollScreen();
void createMapTiles();
void Kill_Graphics();
void renderTiles(LPDIRECT3DTEXTURE9, Sprite);
int getScrollX();
int getScrollY();
void setScrollX(int);
void setScrollY(int);
LPDIRECT3DDEVICE9 getDirect3dDevice();
#endif