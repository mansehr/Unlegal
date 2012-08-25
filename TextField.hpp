			//////////////////////////////////////////////////////////
			//														//
			//			Fil: "TextField.hpp"						//
			//														//
			//			Författad av: Andreas Sehr 2002,01,19		//
			//														//
			//			Senast ändrad:	2002,01,19					//
			//														//
			//////////////////////////////////////////////////////////

class TextField : virtual public Objekt
{
	public:
		TextField();

		char* getText() { return string.getString(); }
		char getText(int i) const { return string[i]; }
		char* getVisualText() { return visualString.getString(); }
		char getVisualText(int i) const { return visualString[i]; }

		void setText (const char* initString) { string = initString; recount(); }
		void setVisualText (const char* initVisualString) { visualString = initVisualString; }
		void addToVisualText (const char* initVisualString) { visualString += initVisualString; }
		void addToVisualText (const char initVisualChar) { visualString += initVisualChar; }
		void setTop (int initTop) {top = initTop; recount();}
		void setBottom (int initBottom) { bottom = initBottom; recount();}
		void setLeft (int initLeft) {left = initLeft; recount();}
		void setRight ( int initRight) {right = initRight; recount();}
		void setWidth (int initWidth) {width = initWidth; recount();}
		void setHeight (int initHeight) {height = initHeight; recount();}

		void draw();
		void test(int x_mouse, int y_mouse);

//	protected:

//	private:
		void recount();
		void updateString();
		void moveStringPosRight();
		void moveStringPosLeft();
		void setTheLinePos(int initPos);
		int theLinePos;		//Linjen som blinkar, så man vet var man är. X led..
		int stringPos;		//Var befinner sig linjen i strängen. används i index
		int visualStringStart;
		String string;
		String visualString; //Den string som visas inom ramen...
};

TextField::TextField()
{
	string = "";
	visualString = "";
	visualStringStart = 0;
}

void TextField::moveStringPosLeft()
{
	if (stringPos > 0)
	{
		stringPos--;

		if (visualStringStart > 0 && stringPos < visualStringStart )
			{ visualStringStart -= 8; }

		if (visualStringStart < 0)
			{ visualStringStart = 0; }
	}
}

void TextField::moveStringPosRight()
{
	if (stringPos < string.getLen())
	{
		stringPos++;

		String tempString("");
		int tempVisualStringStart = visualStringStart;
		for (int i = 0 + visualStringStart; i < stringPos; ++i)
		{
			tempString += string[i];
			if(text_length(font, tempString.getString() ) > getTextWidth())
				{ tempVisualStringStart += 1; }
		}
		visualStringStart = tempVisualStringStart;
	}
}

void TextField::setTheLinePos(int initPos)
{
	if(initPos >= 0 && initPos < getRight())
		{ theLinePos = left + 4 + initPos; }
}

void TextField::recount()
{
	bottom = height + top + 4 + text_height(font);
	right = width + left;
	textWidth = width - 10;

	updateString();
}

void TextField::updateString()
{
	visualString.setToNull();
	for (int i = visualStringStart; text_length(font, visualString.getString() ) < getTextWidth() && i < string.getLen(); ++i)
		{ visualString +=	string[i]; }

	if (stringPos == 0)
		{ setTheLinePos(0); }
	else
	{
		String tempString("");
		for (int i = visualStringStart; i < stringPos; ++i)
		{
			tempString += string[i];
			setTheLinePos(text_length(font, tempString.getString()));
		}
	}
}

void TextField::test(int x_mouse, int y_mouse)
{
	if( getLeft() < x_mouse && getRight() > x_mouse &&
		getTop() < y_mouse && getBottom() > y_mouse)
	{
		clear_keybuf();
		if (mouse_b & 1)
			{ setStatus(Active); }
	}
	else if (mouse_b & 1)
	{
		stringPos = 0;
		setTheLinePos(0);
		setStatus(Null);
	}

	if (!(mouse_b & 1) && getStatus() == Active)
		{ setStatus( Pressed );	}

	if(getStatus() == Active )
	{
		String tempString("");
		setTheLinePos(0);
		stringPos = 0;
		for (int i = 0; i < visualString.getLen() && theLinePos < x_mouse; ++i)
		{
			stringPos = i+1+visualStringStart;
			tempString += visualString[i];
			setTheLinePos(text_length(font, tempString.getString()));
		}
	}

	if (keypressed() == TRUE && (getStatus() == Active || getStatus() == Pressed))
	{
		int k = readkey();

		switch (k)
		{
			case 21248: string.deleteChar(stringPos+1); break; //delete
			case 19200: moveStringPosLeft(); break; //Left
			case 19712: moveStringPosRight(); break; //höger
		}
	/*		Kan annvändas senare till nått??? Programmera senare
		if (key_shifts & KB_SHIFT_FLAG) printf("shift ");
		if (key_shifts & KB_CTRL_FLAG) printf("ctrl ");
		if (key_shifts & KB_ALT_FLAG) printf("alt ");
		if (key_shifts & KB_LWIN_FLAG) printf("lwin ");
		if (key_shifts & KB_RWIN_FLAG) printf("rwin ");
		if (key_shifts & KB_MENU_FLAG) printf("menu ");
	*/
		switch ( k & 0xFF) {
			case 0: break;	//inget tecken
			case 13: break; //Enter, Testa om den blev typ entrad eller nåt ??
			case 8: string.deleteChar(stringPos); moveStringPosLeft(); break;	//Backsteg
			//åäö och ÅÄÖ
			case 91 : string.putIn('å', stringPos); moveStringPosRight(); break;
			case 39 : string.putIn('ä', stringPos); moveStringPosRight(); break;
			case 59 : string.putIn('ö', stringPos); moveStringPosRight(); break;
			case 123: string.putIn('Å', stringPos); moveStringPosRight(); break;
			case 34 : string.putIn('Ä', stringPos); moveStringPosRight(); break;
			case 58 : string.putIn('Ö', stringPos); moveStringPosRight(); break;
			//vanlig bokstav eller tecken som inte känts igen.
			default: string.putIn((k & 0xFF), stringPos); moveStringPosRight(); break;
		}
		updateString();
	}
}

void TextField::draw()
{
//Bakgrund
	rectfill(bmp, getLeft(), getTop(), getRight(), getBottom(), WHITE);
//Texten
	textout(bmp, font, getVisualText() , getLeft() + 4 , getTop() + 6, BLACK);
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

	if ((getStatus() == Active || getStatus() == Pressed) && (retrace_count % 20) < 10)
	{
		line(bmp, theLinePos, getTop()+3, theLinePos, getBottom()-3, BLACK);
		line(bmp, theLinePos-1, getTop()+3, theLinePos-1, getBottom()-3, BLACK);
	}
}
