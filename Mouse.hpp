			//////////////////////////////////////////////////////////
			//														//
			//			Fil: "Mouse.hpp"							//
			//														//
			//			Författad av: Andreas Sehr 2002,01,19		//
			//														//
			//			Senast ändrad:	2002,01,19					//
			//														//
			//////////////////////////////////////////////////////////

class Mouse {
	public:
		Mouse();
		~Mouse();

		BITMAP* getMouseIMG(int initIMG);
		BITMAP* getActiveIMG() {return image[activeIMG];}
		int getX() {return itsX;}
		int getY() {return itsY;}

		void move();

		void setActiveIMG(int initIMG);
		void setXY(int initX, int initY);
	private:
		BITMAP** image;
		int antIMG;
		int activeIMG;
		int itsX, itsY;
		float sensitivity;
};

Mouse::Mouse()
{
	activeIMG = 0;
	sensitivity = 1.25;
	antIMG = 4;
	itsX = 0; itsY = 0;
	image = new BITMAP*[antIMG];
	image[0] = load_bmp("mouse1.1bm",pal);
	image[1] = load_bmp("mouse2.1bm",pal);
	image[2] = load_bmp("mouse3.1bm",pal);
	image[3] = load_bmp("mouse4.1bm",pal);
}

Mouse::~Mouse()
{
}

BITMAP* Mouse::getMouseIMG(int initIMG)
{
	if (initIMG < antIMG)
		return image[initIMG];
	else
		return image[0];
}
void Mouse::move()
{
	fout<<"2"<<endl;
	int mouse_move_x, mouse_move_y;
	fout<<"3"<<endl;
	get_mouse_mickeys(&mouse_move_x, &mouse_move_y);
	fout<<"4"<<endl;
	setXY(itsX + int (mouse_move_x*sensitivity), itsY + int (mouse_move_y*sensitivity));
	fout<<"5"<<endl;
}

void Mouse::setActiveIMG(int initIMG)
{
	if(initIMG < antIMG)
		activeIMG = initIMG;
}

void Mouse::setXY(int initX, int initY)
{
	if(initX >= 0 && initX <= SCREEN_W)
		itsX = initX;
	else if (initX < 0)
		itsX = 0;
	else itsX = SCREEN_W;
fout<<initX<<" "<<SCREEN_W<<" "<<itsX<<endl;
	if(initY >= 0 && initY <= SCREEN_H)
		itsY = initY;
	else if (initY < 0)
		itsY = 0;
	else itsY = SCREEN_H;
fout<<initY<<" "<<SCREEN_H<<" "<<itsY<<endl;
}
