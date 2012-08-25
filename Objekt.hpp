			//////////////////////////////////////////////////////////
			//														//
			//				Fil: "Objekt.hpp"						//
			//														//
			//				Författad av: Andreas Sehr 2002,01,07	//
			//														//
			//				Senast ändrad:	2002,01,07				//
			//														//
			//////////////////////////////////////////////////////////

class Objekt {
	public:
		Objekt();


		char* getText() const {return text;}
		int getTop() const {return top;}
		int getBottom() const {return bottom;}
		int getLeft() const {return left;}
		int getRight() const {return right;}
		int getWidth() const {return width;}
		int getHeight() const {return height;}
		int getTextWidth() const {return textWidth;}
		int getTextHeight() const {return textHeight;}
		Status getStatus() const {return thisStatus;}

		void setText (char* initText);
		void setTop (int initTop) {top = initTop;}
		void setBottom (int initBottom) { bottom = initBottom; }
		void setLeft (int initLeft) {left = initLeft;}
		void setRight ( int initRight) {right = initRight;}
		void setWidth (int initWidth) {width = initWidth;}
		void setHeight (int initHeight) {height = initHeight;}
		void setStatus (Status initStatus) {thisStatus = initStatus;}
		void setTextWidth(int initWidth) {textWidth = initWidth;}

	protected:
		char *text;
		int top;
		int bottom;
		int left;
		int right;
		int width;
		int height;
		int textWidth;
		int textHeight;
		Status thisStatus;

};

Objekt::Objekt()
 {
	setText ("");
	thisStatus = Null;
	top = 0;
	bottom = top + height;
	left = 0;
	right = left + width;
}

void Objekt::setText(char* initText)
{
	text = initText;
	textWidth = text_length(font, text );
	width = textWidth;
	textHeight = text_height(font);
	height = textHeight;
}
