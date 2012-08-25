			//////////////////////////////////////////////////////////
			//														//
			//			Fil: "MenuButton.hpp"						//
			//														//
			//			Författad av: Andreas Sehr 2002,02,12		//
			//														//
			//			Senast ändrad:	2002,02,12					//
			//														//
			//////////////////////////////////////////////////////////

class MenuButton : public Button
{
	public:
		MenuButton() : Button() {}
		MenuButton(char* initString) : Button(initString) {}
		void draw();
};

void MenuButton::draw()
{
	if (getStatus() == Null)
	{
	//Texten
		textout(bmp, font, getText(), getTextPosX(), getTextPosY(), getTextColor());
	}
	else {
	//Bakgrund
		rectfill(bmp, getLeft(), getTop(), getRight(), getBottom(), GREY);
	//Texten
		textout(bmp, font, getText(), getTextPosX(), getTextPosY(), getTextColor());

		COLOUR farg1, farg2, farg3, farg4;
		if ( getStatus() == Pressed || getStatus() == Active)
		{
		//Insjunken Knapp
			farg1 = WHITE;
			farg2 = BLACK;
			farg3 = DARKGREY;
			farg4 = LIGHTGREY;
		}
		else {
		//Vanlig Knapp
			farg1 = BLACK;
			farg2 = WHITE;
			farg3 = LIGHTGREY;
			farg4 = DARKGREY;
		}
	//Yttre boxen
		line(bmp, getLeft(), getBottom(), getRight(), getBottom(), farg1);
		line(bmp, getRight(), getBottom(), getRight(), getTop(), farg1);
		line(bmp, getLeft(), getBottom()-1, getLeft(), getTop(), farg2);
		line(bmp, getLeft(), getTop(), getRight()-1, getTop(), farg2);
	//Inre boxen
		line(bmp, getLeft()+1, getBottom()-1, getLeft()+1, getTop()+1, farg3);
		line(bmp, getLeft()+1, getTop()+1, getRight()-1, getTop()+1, farg3);
		line(bmp, getRight()-1, getBottom()-1, getRight()-1, getTop()+1, farg4);
		line(bmp, getLeft()+1, getBottom()-1, getRight()-1, getBottom()-1, farg4);
	}
}
