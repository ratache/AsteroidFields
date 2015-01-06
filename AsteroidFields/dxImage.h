#include <string>

/*
Image class for handling surfaces.
*/
class Image{
private:
	const char *path;
	int posx, posy, width, height;
	float scale;

public:
	Image(const char *path, int posx = 0, int posy = 0, float fscale = 1.0);
	~Image();

	std::string getPath();
	int getPosX();
	int getPosY();
	//int getWidth();
	//int getHeight();
	float getScale();

	void setPosX(int);
	void setPosY(int);
	//void setWidth(int);
	//void setHeight(int);
	void setScale(float);
};