			//////////////////////////////////////////////////////////
			//														//
			//			Fil: "Button.hpp"							//
			//														//
			//			Författad av: Andreas Sehr 2002,01,07		//
			//														//
			//			Senast ändrad:	2002,01,07					//
			//														//
			//////////////////////////////////////////////////////////


class Button : public Objekt
{
	public:
		Button() {textPos.setX(0); textPos.setY(0); setText("Error");}
		Button( char *initText, int x = 0, int y = 0);

		int getTextPosX() {return textPos.getX();}
		int getTextPosY() {return textPos.getY();}
		int getMarginVertical() const {return marginVertical;}
		int getMarginHorizontal() const {return marginHorizontal;}
		int getTextColor() {return 0; }

		void setMargin( int initMargin );
		void setWidth( int initWidth );

		void setTop (int initTop) {top = initTop; reCount();}
		void setBottom (int initBottom) { bottom = initBottom; reCount();}
		void setLeft (int initLeft) {left = initLeft; reCount();}
		void setRight ( int initRight) {right = initRight; reCount();}
		void setHeight (int initHeight) {height = initHeight; reCount();}


		void draw();

	private:
		int marginVertical;
		int marginHorizontal;
		static const int lines = 2;	//Två linjer ligger inom objektet...
		Point textPos;

		void reCount();		//Annvänds bara av klassen
};

Button::Button( char *initText, int x = 0, int y = 0)
{
	setText(initText);

	marginVertical = 1;
	marginHorizontal = 1;

	left = x;
	top = y;
	bottom = height + top + lines;
	right = width + left + lines;

	reCount();
}

void Button::setMargin(int initMargin)
{
	marginVertical = initMargin;
	marginHorizontal = initMargin;

	reCount();
}

void Button::setWidth( int initWidth )
{
	if (initWidth < textWidth)
		initWidth = textWidth;

	marginHorizontal = (initWidth - textWidth)/2;

	reCount();
}

void Button::reCount()
{
	height = (marginVertical*2) + lines + textHeight;
	width = (marginHorizontal*2) + lines + textWidth;

	bottom = top + height;
	right = left + width;

	textPos.setX(left + marginHorizontal + 2);
	textPos.setY(top  + marginVertical + 2);
}

void Button::draw()
{
	COLOUR farg1, farg2, farg3, farg4;
	if ( getStatus() == Pressed || getStatus() == Active)
	{
		farg1 = WHITE;
		farg2 = BLACK;
		farg3 = DARKGREY;
		farg4 = LIGHTGREY;
	}
	else {
		farg1 = BLACK;
		farg2 = WHITE;
		farg3 = LIGHTGREY;
		farg4 = DARKGREY;
	}
//Bakgrund
	rectfill(bmp, getLeft(), getTop(), getRight(), getBottom(), GREY);
//Texten
	textout(bmp, font, getText(), getTextPosX(), getTextPosY(), getTextColor());
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
