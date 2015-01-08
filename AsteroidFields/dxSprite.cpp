#include "dxSprite.h"

/*	Sprite - class
**************************************************
This class is representing the sprite.
To create a sprite object we need the following:
id and the surface object to determine size of the sprite.
All other valus will be set to default values.

**************************************************
Default values:
**************************************************
Frames current, last = 0, 0
Animation delay, count = 0, 0
Movement x,y = 0,0

**************************************************
These values are easily changed after the sprite
has been created in memory with properties access.
*/
Sprite::Sprite(){
	movex, movey, curframe, lastframe, animcount, animdelay = 0;
	setPosition();
	color = D3DCOLOR_ARGB(255, 255, 255, 255);
}

Sprite::Sprite(int x, int y){
	setPosX(x);
	setPosY(y);
	setPosition(x,y);
	color = D3DCOLOR_ARGB(255, 255, 255, 255);
}

bool Sprite::populate(LPDIRECT3DDEVICE9 dev, std::string inParam, int width, int height){
	setPosX(x);
	setPosY(y);
	
	//D3DXCreateTextureFromFile
	if (!SUCCEEDED(D3DXCreateTextureFromFileEx(dev, inParam.c_str(), width, height, 
		D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT,
		0, NULL, NULL, &texture)))
	{
		MessageBox(NULL, "Error initializing the sprite", "Error", MB_OK);
		return 0;
	}

	if (!SUCCEEDED(D3DXCreateSprite(dev, &sprite))){
		MessageBox(NULL, "Error creating the sprite", "Error", MB_OK);
		return 0;
	}

	return 1;

}

void Sprite::DrawThis()
{
	if (sprite && texture)
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		sprite->Draw(texture, NULL, NULL, &position, color);
		sprite->End();
	}
}

///////GETTERS////////////
std::string Sprite::getPath(){
	return path;
}

int Sprite::getPosX(){
	return position.x;
}
int Sprite::getPosY(){
	return position.y;
}
D3DXVECTOR3 Sprite::getPosition(){
	return position;
}
int Sprite::getHeight(){
	return height;
}
int Sprite::getWidth(){
	return width;
}
int Sprite::getMoveX(){
	return movex;
}
int Sprite::getMoveY(){
	return movey;
}
int Sprite::getFrameCurrent(){
	return curframe;
}
int Sprite::getFrameLast(){
	return lastframe;
}
int Sprite::getAnimDelay(){
	return animdelay;
}
int Sprite::getAnimCount(){
	return animcount;
}
D3DCOLOR Sprite::getColor(){
	return color;
}

///////SETTERS////////////
void Sprite::setPath(std::string in){
	path = in;
}

void Sprite::setPosX(int px){
	position.x = px;
}
void Sprite::setPosY(int py){
	position.y = py;
}
void Sprite::setPosition(int x, int y){
	position.x = x;
	position.y = y;
}
void Sprite::setHeight(int h){
	height = h;
}
void Sprite::setWidth(int w){
	width = w;
}
void Sprite::setMoveX(int mx){
	movex = mx;
}
void Sprite::setMoveY(int my){
	movey = my;
}
void Sprite::setFrameCurrent(int fc){
	curframe = fc;
}
void Sprite::setFrameLast(int fl){
	lastframe = fl;
}
void Sprite::setAnimDelay(int ad){
	animdelay = ad;
}
void Sprite::setAnimCount(int ac){
	animcount = ac;
}
void Sprite::setColor(int r, int g, int b){
	color = D3DCOLOR_ARGB(255, r, g, b);
}

///DESTROYER OF WORLDS
Sprite::~Sprite(){
	if (sprite != NULL){
		sprite->Release();
	}
	if (texture != NULL){
		texture->Release();
	}

}
