#include "Engine.h"


//timing variable
long start = GetTickCount();
//PLAYER SPRITE
Sprite* player;
LPDIRECT3DTEXTURE9 kittytx[7];
LPDIRECT3DSURFACE9 back;
LPD3DXSPRITE sh;

bool Game_Init(HWND hwnd)
{
	Init_DirectInput(hwnd);
	Init_Keyboard(hwnd);
	Init_Mouse(hwnd);
	Init_Graphics(hwnd);

	start = GetTickCount();
	createMapTiles();
	player = new Sprite(100, 100);

	//////////////////////////
	//// init objects
	/////////////////////////
	
	//load the sprite animation for player
	int n;
	char s[20];
	for (n = 0; n<6; n++)
	{
		//set up the filename
		sprintf_s(s, "cat%d.bmp", n + 1);

		//load texture with "pink" as the transparent color
		kittytx[n] = LoadTexture(s, D3DCOLOR_XRGB(255, 0, 255));
		if (kittytx[n] == NULL)
			return 0;
	}
	//////////////////////////////////////////////////
	//set object initial parameters
	/////////////////////////////////////////////////
	player->setPosX(100);
	player->setPosY(150);
	player->setWidth(96);
	player->setHeight(96);
	player->setFrameCurrent(0);
	player->setFrameLast(5);
	player->setAnimDelay(2);
	player->setAnimCount(0);
	player->setMoveX(8);
	player->setMoveY(0);

	player->setColor(255, 255, 255);

	return 1;
}

/* <-GAME RUN->
There are two parts to the Game_Run function. The first part should move and
animate the sprite(s) in the game. The second part should draw the sprite(s) to
the screen. The reason that a screen update is divided into two parts (one for
logic, the other for screen refresh) is because you don’t want to take too much
processing time in between the BeginScene and EndScene calls, so keep the code
there to the minimum required to update the graphics and leave other processing
tasks for either before or after the screen update.
*/
void Game_Run(HWND hWnd)
{
	//////////////////////////////////////////////////////////////////////////////
	// UPDATE AND RENDER GAME
	/////////////////////////////////////////////////////////////////////////////
	//poll DirectInput devices
	Poll_Keyboard();
	Poll_Mouse();
	int sX = getScrollX();
	int sY = getScrollY();

	//check for escape key (to exit program)
	if (Key_Down(DIK_ESCAPE))
		PostMessage(hWnd, WM_DESTROY, 0, 0);
	//scroll based on mouse input
	if (Mouse_X() != 0){
		sX += Mouse_X();
		setScrollX(sX);
	}
	if (Mouse_Y() != 0){
		sY+= Mouse_Y();
		setScrollY(sY);
	}
	//after short delay, ready for next frame?
	//this keeps the game running at a steady frame rate
	if (GetTickCount() - start >= 30)
	{
		//check for keyboard input
		if (Key_Down(DIK_LEFT)){
			sX -= 5;
			player->setMoveX(sX);
			setScrollX(sX);
		}
		if (Key_Down(DIK_RIGHT)){
			sX += 5;
			player->setMoveY(sX);
			setScrollX(sX);
		}
		if (Key_Down(DIK_DOWN)){
			sY += 5;
			setScrollY(sY);
		}
		if (Key_Down(DIK_UP)){
			sY -= 5;
			setScrollY(sY);
		}
		//////////
		//Check anim delay
		int animcount = player->getAnimCount();
		player->setAnimCount(animcount + 1);
		if (player->getAnimCount()  > player->getFrameLast())
		{
			player->setAnimCount(0);
			player->setFrameCurrent((player->getFrameCurrent() +1 ));
			if (player->getFrameCurrent() > player->getFrameLast()){
				player->setFrameCurrent(0);
			}
		}



		//reset timing
		start = GetTickCount();
		////renderShip();
		//renderBackgroundTiles();

		renderTiles(kittytx[player->getFrameCurrent()],*player);
	}
}

void Game_End()
{
	delete player;
	Kill_Keyboard();
	Kill_Mouse();
	dinput->Release(); 
	Kill_Graphics();
}