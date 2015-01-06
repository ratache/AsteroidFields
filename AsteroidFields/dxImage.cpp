#include "dxImage.h"

/*
These are the functions for the image class object.
This class is intended for easy storage of
image properties.You can set
whatever size and scale of your picture here
(because the direct3d stuff hasn't been created
yet). You send this object to the wrapper which
then draws whatever this object points to and defines.
*/
Image::Image(const char *supposedPath, int x, int y, float fscale){
	path = supposedPath;
	posx = x;
	posy = y;
	scale = fscale;
}

/////////////////GETTERS
std::string Image::getPath(){
	return path;
}
int Image::getPosX(){
	return posx;
}
int Image::getPosY(){
	return posy;
}
//int Image::getWidth(){
//	return width;
//}
//int Image::getHeight(){
//	return height;
//}
float Image::getScale(){
	return scale;
}

//////////////////SETTERS
void Image::setPosX(int x){
	posx = x;
}
void Image::setPosY(int y){
	posy = y;
}
//void Image::setWidth(int w){
//	width = w;
//}
//void Image::setHeight(int h){
//	height = h;
//}
void Image::setScale(float s){
	scale = s;
}
///DESTROYER OF WORLDS
Image::~Image(){
}
