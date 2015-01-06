#ifndef _ENGINE_H
#define _ENGINE_H

#include <string>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <d3dx9math.h>
#include "dxGraphics.h"
#include "dxImage.h"
#include "dxText.h"
#include "dxaudio.h"
#include "dxinput.h"

//data for the scrolling map
#define TILEWIDTH 64
#define TILEHEIGHT 64
#define MAPWIDTH 25
#define MAPHEIGHT 18
#define GAMEWORLDWIDTH (TILEWIDTH * MAPWIDTH)
#define GAMEWORLDHEIGHT (TILEHEIGHT * MAPHEIGHT)

//macros to read the keyboard asynchronously
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

//function prototypes
bool Game_Init(HWND);
void Game_Run(HWND);
void Game_End(HWND);

//scrolling map support functions
void ScrollScreen();
void BuildGameWorld();
void DrawTile(LPDIRECT3DSURFACE9, int, int, int, int, LPDIRECT3DSURFACE9, int, int);

#endif