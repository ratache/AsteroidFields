#include "dxText.h"

Text::Text(const char* t, int posx, int posy, int size, DWORD color){
	text = t;
	setTextSize(size);
	setPosX(posx);
	setPosY(posy);
	setColor(color);
}

////////////GETTERS
int Text::getPosX()
{
	return  posx;
}
int Text::getPosY(){
	return posy;
}
DWORD Text::getColor(){
	return color;
}
int Text::getSize(){
	return size;
}
std::string Text::getText(){
	return text;
}

/////////SETTERS
void Text::setPosX(int x){
	posx = x;
}
void Text::setPosY(int y){
	posy = y;
}
void Text::setColor(DWORD c){
	color = c;
}
void Text::setTextSize(int s){
	size = s;
}
/////////DESTROYER
Text::~Text(){
}