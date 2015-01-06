/*
Sprite class for handling 2d functionality
*/
#include <string>

class Sprite{
private:
	int x, y, width, height, movex, movey, curframe, lastframe, animdelay, animcount;
public:
	Sprite();
	~Sprite();

	int getPosX();
	int getPosY();
	int getHeight();
	int getWidth();
	int getMoveX();
	int getMoveY();
	int getFrameCurrent();
	int getFrameLast();
	int getAnimDelay();
	int getAnimCount();

	void setPosX(int);
	void setPosY(int);
	void setHeight(int);
	void setWidth(int);
	void setMoveX(int);
	void setMoveY(int);
	void setFrameCurrent(int);
	void setFrameLast(int);
	void setAnimDelay(int);
	void setAnimCount(int);
};