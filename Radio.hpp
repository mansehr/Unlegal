			//////////////////////////////////////////////////////////
			//														//
			//			Fil: "Radio.hpp"							//
			//														//
			//			Författad av: Andreas Sehr 2002,01,07		//
			//														//
			//			Senast ändrad:	2002,01,07					//
			//														//
			//////////////////////////////////////////////////////////

class Radio {
	public:
		Radio() {bAntal = 0;}

		int getAntalButtons() {return bAntal;}
		Button* getButton (int nr) {return button[nr];}
		Button* getActiveButton() {return activeButton;}

		void add(Button &initButton);

		void setActiveButton(Button *initActiveButton) {activeButton = initActiveButton;}

	private:
		Button *button[5];
		Button *activeButton;
		int bAntal;
};

void Radio::add(Button &initButton)
{
	button[bAntal] = &initButton;
	if (bAntal == 0)
	{
		button[bAntal]->setStatus(Pressed);
		activeButton = button[bAntal];
	}
	++bAntal;
}
