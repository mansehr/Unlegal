			//////////////////////////////////////////////////////////
			//														//
			//			Fil: "RitaObjekt.hpp"						//
			//														//
			//			Författad av: Andreas Sehr 2002,01,21		//
			//														//
			//			Senast ändrad:	2002,01,21					//
			//														//
			//////////////////////////////////////////////////////////
class RitaObjekt {
	public:
		RitaObjekt() {bAntal = 0; rAntal = 0; tfAntal = 0; lAntal = 0; mbAntal = 0;}
		void add(MenuBar &initMenuBar) { menuBar[mbAntal++] = &initMenuBar; }
		void add(Button &initButton) { button[bAntal++] = &initButton; }
		void add(Button *initButton) { button[bAntal++] = initButton; }
		void add(Radio &radio);
		void add(TextField &initTextField) { textField[tfAntal++] = &initTextField; }
		void add(List &initList) { list[lAntal++] = &initList; }

		void all();
		void buttons();
		void textFields();
		void lists();
		void menuBars();

	private:
		MenuBar *menuBar[2];
		Button *button[20];
		TextField *textField[10];
		List *list[5];
		int bAntal;
		int rAntal;
		int tfAntal;
		int lAntal;
		int mbAntal;
};


void
RitaObjekt::add(Radio &initRadio)
{
	for (int i = 0; i < initRadio.getAntalButtons(); ++i)
		add( initRadio.getButton(i) );
}

void
RitaObjekt::buttons()
{
	for (int i = 0; i < bAntal; ++i )
		button[i]->draw();
}

void
RitaObjekt::textFields()
{
	for (int i = 0; i < tfAntal; ++i )
		textField[i]->draw();
}

void RitaObjekt::lists()
{
	for (int i = 0; i < lAntal; ++i)
		list[i]->draw();
}

void RitaObjekt::menuBars()
{
	for (int i = 0; i < mbAntal; ++i)
		menuBar[i]->draw();
}

void RitaObjekt::all()
{
	buttons();
	lists();
	menuBars();
	textFields();
}
