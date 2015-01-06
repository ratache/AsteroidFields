#include <string>
#include <d3dx9.h>
/*
Text class for handling text to be drawn.
*/
class Text{
private:
	const char *text;
	int posx, posy, size;
	DWORD color;
public:
	Text(const char*, int x, int y, int size, DWORD color = 0);
	~Text();

	int getPosX();
	int getPosY();
	DWORD getColor();
	int getSize();
	std::string getText();

	void setTextSize(int);
	void setPosX(int);
	void setPosY(int);
	void setColor(DWORD);
};