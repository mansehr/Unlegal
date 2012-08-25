			//////////////////////////////////////////////////////////
			//														//
			//				Fil: "List.hpp"						//
			//														//
			//				Författad av: Andreas Sehr 2002,02,06	//
			//														//
			//				Senast ändrad:	2002,02,06				//
			//														//
			//////////////////////////////////////////////////////////
//-------------------------------------------Class ListObjekt---------------------------------------
class ListObjekt : public Objekt
{
	public:
		ListObjekt() {string = "";}

		void setText(String initString);

		void setTop (int initTop) {top = initTop; bottom = top + height;}
		void setLeft (int initLeft) {left = initLeft; right = left + width;}
		void setWidth (int initWidth) {width = initWidth; right = left + width;}
		void setHeight (int initHeight) {height = initHeight; bottom = top + height;}

		char* getString() { return string.getString(); }

		bool test(int y_mouse);
		void draw();

	private:
		String string;
};

void ListObjekt::setText(String initString)
{
	string = initString;
}

bool ListObjekt::test(int y_mouse)
{
	if (getStatus() == NotPressable)
		return false;

	if ( y_mouse >= getTop() && y_mouse <= getBottom() )
	{
		if (mouse_b & 1)
		{
			setStatus(Active);
			return true;
		}

		if (getStatus() != Active)
			setStatus(Hoover);
	}
	else if (getStatus() != Active)
	{
		setStatus(Null);
		return false;
	}
}

void ListObjekt::draw()
{
	int textColor;

	if (getStatus() == NotPressable)
	{
		textColor = DARKGREY;
	}
	else {
		textColor = BLACK;
	}

	if (getStatus() == Active)
	{
		rectfill(bmp, getLeft(), getTop(), getRight(), getBottom(), BLUE);

		line(bmp, getLeft(), getTop(), getLeft(), getBottom(), BLACK);
		line(bmp, getLeft(), getTop(), getRight(), getTop(), BLACK);
		line(bmp, getRight() , getTop(), getRight(), getBottom(), BLACK);
		line(bmp, getLeft(), getBottom(), getRight(), getBottom(), BLACK);

		textColor = WHITE;
	}

	textout(bmp, font, getString() , getLeft() + 2 , getTop() + 2, textColor);
}


//-------------------------------------------Class List---------------------------------------------
class List : public Objekt
{
	public:
		List() {lAntal = 0; activeListObjekt = 0;}

		void add(String initString);
		void test(int y_mouse, int x_mouse);
		void draw();

		void setTop (int initTop) {top = initTop; bottom = top + height;}
		void setLeft (int initLeft) {left = initLeft; right = left + width;}
		void setWidth (int initWidth) {width = initWidth; right = left + width;}
		void setHeight (int initHeight) {height = initHeight; bottom = top + height;}

		void setListObjektStatus(int i, Status initStatus) {lObjekt[i].setStatus(initStatus);}
		void setListObjektString(int i, String initString) {lObjekt[i].setText(initString);}
		int getListObjektAntal() const { return lAntal; }

		ListObjekt getActiveListObjekt() const { return *activeListObjekt; }
		int getActiveListObjektNr() const;

	private:
		int lAntal;
		ListObjekt *activeListObjekt;
		ListObjekt lObjekt[50];
};

void List::add(String initString)
{
	lObjekt[lAntal].setText( initString );
	lObjekt[lAntal].setLeft( getLeft()+1 );
	lObjekt[lAntal].setRight( getRight()-1 );
	lObjekt[lAntal].setTop(bottom);
	lObjekt[lAntal].setBottom( text_height(font) + lObjekt[lAntal].getTop() + 3);
	bottom = lObjekt[lAntal].getBottom() + 3;
	lObjekt[lAntal].setStatus(thisStatus);
	activeListObjekt = 0;
	++lAntal;
}

void List::test( int x_mouse, int y_mouse)
{
	if (y_mouse > getTop() && y_mouse < getBottom()
		&& x_mouse > getLeft() && x_mouse < getRight())
	{
		setStatus(Hoover);

		for (int i = 0; i < lAntal; ++i)
		{
			if ((lObjekt[i].test(y_mouse) == true) && (activeListObjekt != &lObjekt[i]))
			{
				if (activeListObjekt->getStatus() == NotPressable)
					activeListObjekt->setStatus(NotPressable);
				else
					activeListObjekt->setStatus(Null);

				activeListObjekt = &lObjekt[i];
			}
		}

		if (mouse_b & 1)
			setStatus(Active);
	}
	else setStatus(Null);
}

void List::draw()
{
//Bakgrunden
	rectfill(bmp, getLeft(), getTop(), getRight(), getBottom(), WHITE);
//Yttre boxen
	line(bmp, getLeft(), getTop(), getRight(), getTop(), DARKGREY);
	line(bmp, getLeft(), getBottom(), getRight(), getBottom(), LIGHTGREY);
	line(bmp, getLeft(), getTop(), getLeft(), getBottom(), DARKGREY);
	line(bmp, getRight(), getTop(), getRight(), getBottom(), LIGHTGREY);
//Inre boxen
	line(bmp, getLeft()+1, getTop()+1, getRight()-1, getTop()+1, BLACK);
	line(bmp, getLeft()+1, getBottom()-1, getRight()-1, getBottom()-1, WHITE);
	line(bmp, getLeft()+1, getTop()+1, getLeft()+1, getBottom()-1, BLACK);
	line(bmp, getRight()-1, getTop()+1, getRight()-1, getBottom()-1, WHITE);
//Texten från ListObjekten
	for (int i = 0; i < getListObjektAntal(); i++)
		lObjekt[i].draw();
}

int List::getActiveListObjektNr() const
{
	for (int i = 0; i < lAntal; ++i)
	{
		if (activeListObjekt == &lObjekt[i])
			return i;
	}
	return 0;
}
