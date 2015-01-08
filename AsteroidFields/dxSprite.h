#ifndef _SPRITE
#define _SPRITE

/*
Sprite class for handling 2d functionality
*/
#include <string>
#include <d3dx9.h>

class Sprite{
private:
	int x, y, width, height, movex, movey, curframe, lastframe, animdelay, animcount;
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	D3DXVECTOR3 position;
	D3DCOLOR color;
	std::string path;
public:
	Sprite();
	Sprite(int x = 0, int y= 0);
	~Sprite();

	bool populate(LPDIRECT3DDEVICE9, std::string, int width, int height);
	void DrawThis();

	std::string getPath();
	int getPosX();
	int getPosY();
	D3DXVECTOR3 getPosition();
	int getHeight();
	int getWidth();
	int getMoveX();
	int getMoveY();
	int getFrameCurrent();
	int getFrameLast();
	int getAnimDelay();
	int getAnimCount();
	D3DCOLOR getColor();
	
	void setPath(std::string);
	void setPosX(int);
	void setPosY(int);
	void setPosition(int x = 0, int y = 0);
	void setHeight(int);
	void setWidth(int);
	void setMoveX(int);
	void setMoveY(int);
	void setFrameCurrent(int);
	void setFrameLast(int);
	void setAnimDelay(int);
	void setAnimCount(int);
	void setColor(int, int, int);
};
#endif