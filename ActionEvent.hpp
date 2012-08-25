			//////////////////////////////////////////////////////////
			//														//
			//			Fil: "ActionEvent.hpp"						//
			//														//
			//			Författad av: Andreas Sehr 2002,01,19		//
			//														//
			//			Senast ändrad:	2002,01,19					//
			//														//
			//////////////////////////////////////////////////////////

class ActionEvent {
	public:
		ActionEvent();
		~ActionEvent();

		void setSource(MenuBar &initMenuBar) { setNull(); menuBar = &initMenuBar;}
		void setSource(Menu &initMenu) { setNull(); menu = &initMenu;}
		void setSource(MenuItem &initMenuItem) { setNull(); menuItem = &initMenuItem; }
		void setSource(Button* initButton) { setNull(); button = initButton;}
		void setSource(Button &initRadioButton, bool) { setNull(); radioButton = &initRadioButton;}
		void setSource(List &initList) { setNull(); list = &initList;}


		bool buttons();
		//bool menuBars();
		//bool menus();
		//bool menuItems();

		void setNull();

		bool operator == (const MenuBar &);
		bool operator == (const Menu &);
		bool operator == (const MenuItem &);
		bool operator == (const Button &);
		bool operator == (const Button*);
		bool operator == (const List &);
		bool operator == (const bool);



	private:
		MenuBar *menuBar;
		Menu *menu;
		MenuItem *menuItem;
		Button *button;
		Button *radioButton;
		List *list;
};


ActionEvent::ActionEvent()
{
	menuBar = new MenuBar;
	menu = new Menu;
	menuItem = new MenuItem;
	button = new Button;
	list = new List;
	setNull();
}

ActionEvent::~ActionEvent()
{
	delete menuBar;
	menuBar = 0;

	delete menu;
	menu = 0;

	delete menuItem;
	menuItem = 0;

	delete button;
	button = 0;

	delete list;
	list = 0;
}

bool
ActionEvent::buttons()
{
	if (button != 0)
		return true;
	else
		return false;
}

void ActionEvent::setNull()
{
	menuBar = 0;
	menu = 0;
	menuItem = 0;
	button = 0;
	list = 0;
}


bool
ActionEvent::operator == (const MenuBar &testMenuBar)
{
	if (&testMenuBar == menuBar)			//Om menuBar är aktiv
		return true;
	else return false;
}

bool
ActionEvent::operator == (const Menu &testMenu)
{
	if (&testMenu == menu)			//Om menu är aktiv
		return true;
	else return false;
}

bool
ActionEvent::operator == (const MenuItem &testMenuItem)
{
	if (&testMenuItem == menuItem)			//Om menuItem är aktiv
	{
		return true;}
	else return false;
}

bool
ActionEvent::operator == (const Button &testButton)
{
	if (&testButton == button || &testButton == radioButton)			//Om Button är aktiv
	{
		return true;
	}
	else return false;
}

bool
ActionEvent::operator == (const Button* testButton)
{
	if (testButton == button || testButton == radioButton)			//Om Button är aktiv
	{
		return true;
	}
	else return false;
}

bool
ActionEvent::operator == (const List &testList)
{
	if (&testList == list)		//Om List är aktiv;
		return true;
	else return false;
}

bool
ActionEvent::operator == (const bool initBool)
{
	if (initBool)
	{
		if (button != 0 || menuItem != 0 ||
			menu != 0 || menuBar != 0 )
			return true;
		else return false;
	}
	if (!initBool)
	{
		if (button == 0 && menuItem == 0 &&
			menu == 0 && menuBar == 0)
			return true;
		else return false;
	}
}
