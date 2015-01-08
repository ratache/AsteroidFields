#ifndef _ENGINE_H
#define _ENGINE_H


#include <d3dx9math.h>
#include "dxGraphics.h"
#include "dxInput.h"
#include "dxSprite.h"

//macros to read the keyboard asynchronously
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

//function prototypes
bool Game_Init(HWND);
void Game_Run(HWND);
void Game_End();
#endif