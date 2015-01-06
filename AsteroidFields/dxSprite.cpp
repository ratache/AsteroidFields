#include "dxSprite.h"

/*	Sprite - class
**************************************************
This class is representing the sprite.
To create a sprite object we need the following:
id and the surface object to determine size of the sprite.
All other valus will be set to default values.

ATTENTION: The sprite does not include anything
related to the specific resource.
The sprite object handles the location, speed,
frame and movement of the resources rendered.

**************************************************
Default values:
**************************************************
Position x,y = 0,0
Frames current, last = 0, 0
Animation delay, count = 0, 0
Movement x,y = 0,0

**************************************************
These values are easily changed after the sprite
has been created in memory with properties access.
*/
Sprite::Sprite(){
	x, y, movex, movey, curframe, lastframe, animcount, animdelay = 0;
}

///////GETTERS////////////
int Sprite::getPosX(){
	return x;
}
int Sprite::getPosY(){
	return y;
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

///////SETTERS////////////
void Sprite::setPosX(int px){
	x = px;
}
void Sprite::setPosY(int py){
	y = py;
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

///DESTROYER OF WORLDS
Sprite::~Sprite(){
}
