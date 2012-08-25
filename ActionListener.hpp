			//////////////////////////////////////////////////////////
			//														//
			//			Fil: "ActionListener.hpp"					//
			//														//
			//			Författad av: Andreas Sehr 2002,01,07		//
			//														//
			//			Senast ändrad:	2002,01,07					//
			//														//
			//////////////////////////////////////////////////////////

class ActionListen {
	public:
		ActionListen();

		void add(MenuBar &initMenuBar);
		void add(Menu &initMenu);
		void add(MenuItem &initMenuItem);
		void add(Button &initButton);
		void add(Button* initButton);
		void add(Radio &initRadio);
		void add(List &initList);
		void add(TextField &initTextField);

		void listen(int y_mouse, int x_mouse);
		void toDo(ActionEvent &e);

	private:
		MenuBar *menuBar[5];
		Menu *menu[50];
		MenuItem *menuItem[300];
		Button *button[30];
		Radio *radio[5];
		List *list[5];
		TextField *textField[5];
		MenuBar *activeMenuBar;
		Menu *activeMenu;
		MenuItem *activeMenuItem;
		Button *activeButton;
		List *activeList;
		TextField *activeTextField;
		int mbAntal;	//menuBarAntal
		int mAntal;		//menuAntal
		int miAntal;	//menuItemAntal
		int bAntal;		//buttonAntal
		int rAntal;		//radioAntal
		int lAntal;		//listAntal
		int tfAntal;	//textFieldAndtal
};

ActionListen::ActionListen()
{
	mbAntal = 0;
	mAntal = 0;
	miAntal = 0;
	bAntal = 0;
	lAntal = 0;
	tfAntal = 0;
}

void
ActionListen::add(MenuBar &initMenuBar)
{
	menuBar[mbAntal] = &initMenuBar;
	rita.add(*menuBar[mbAntal]);
	mbAntal++;

}

void
ActionListen::add(Menu &initMenu)
{
	menu[mAntal] = &initMenu;
	mAntal++;
}

void
ActionListen::add(MenuItem &initMenuItem)
{
	menuItem[miAntal] = &initMenuItem;
	miAntal++;
}

void
ActionListen::add(Button &initButton)
{
	button[bAntal] = &initButton;
	rita.add(button[bAntal]);
	bAntal++;
}

void
ActionListen::add(Button* initButton)
{
	button[bAntal] = initButton;
	rita.add(button[bAntal]);
	bAntal++;
}

void
ActionListen::add(Radio &initRadio)
{
	radio[rAntal] = &initRadio;
	rita.add(*radio[rAntal]);
	rAntal++;
}

void
ActionListen::add(List &initList)
{
	list[lAntal] = &initList;
	rita.add(*list[lAntal]);
	lAntal++;
}

void
ActionListen::add(TextField &initTextField)
{
	textField[tfAntal] = &initTextField;
	rita.add(*textField[tfAntal]);
	tfAntal++;
}

void
ActionListen::listen(int y_mouse, int x_mouse)
{
//Testa TextField
	for(int i = 0; i < tfAntal; ++i)
		{ textField[i]->test(x_mouse, y_mouse);	}

//Testa List
	for( int i = 0; i < lAntal; ++i)
		{ list[i]->test(x_mouse,y_mouse); }

//Testa radio
	for (int i = 0; i < rAntal; ++i)
	{
	//Variablerna kan vara interna eftersom radio klassen håller reda på resten
		Button *tempButton;
		Button *activeRadioButton = radio[i]->getActiveButton();

		for (int j = 0; j < radio[i]->getAntalButtons(); ++j)
		{
			tempButton = radio[i]->getButton(j);

			if(y_mouse >= tempButton->getTop() && y_mouse <= tempButton->getBottom()
			   && x_mouse >= tempButton->getLeft() && x_mouse <= tempButton->getRight() )
				if (mouse_b & 1)
				{
					activeRadioButton->setStatus(Null);
					tempButton->setStatus( Pressed );
					activeRadioButton = tempButton;
					radio[i]->setActiveButton(tempButton);
				}
		}
		actionEvent.setSource(*activeRadioButton, true);
	}

//Testa MenuBar
	for (int i = 0; i < mbAntal; ++i)
		if (x_mouse >=  menuBar[i]->getLeft()&& x_mouse <= menuBar[i]->getRight() &&
    	 	y_mouse >= menuBar[i]->getTop() && y_mouse <= menuBar[i]->getBottom() )
		{
			activeMenuBar->setStatus(Null);	//Nollställer Tidigare menuBar
			menuBar[i]->setStatus(Hoover);
			activeMenuBar = menuBar[i];		//Tilldelar activeMenuBar så att den kan nollställas sen

			if (mouse_b & 1)
				{ menuBar[i]->setStatus(Active); }
		}
		else { menuBar[i]->setStatus(Null); }

	if (!(mouse_b & 1) && activeMenuBar->getStatus() == Active)
	{
		activeMenuBar->setStatus(Pressed);
		actionEvent.setSource(*activeMenuBar);
	}

//Testa Menu
	for (int i = 0; i < mAntal; ++i)
		if (x_mouse >= menu[i]->getLeft() && x_mouse <= menu[i]->getRight()
			&& y_mouse >= menu[i]->getTop() && y_mouse <= menu[i]->getBottom()
			&& activeMenuBar->getNr() == menu[i]->getHeadMenuBar() )
		{
		    if (activeMenu->getStatus() == Pressed)
		    {
				activeMenu->setStatus(Null);
				menu[i]->setStatus(Pressed);
				activeMenu = menu[i];
				actionEvent.setSource(*menu[i]);
		    }
		    if (activeMenu->getStatus() == Hoover || activeMenu->getStatus() == Null)
			{
				activeMenu->setStatus( Null );
				menu[i]->setStatus(Hoover);
				activeMenu = menu[i];
			}
			if (mouse_b & 1)// && activeMenu->getStatus() == Pressed)
				{ activeMenu->setStatus(Active); }
		}
		else if (activeMenu->getStatus() != Pressed)
				{ menu[i]->setStatus(Null); }

	if (!(mouse_b & 1) && activeMenu->getStatus() == Active)
	{
		activeMenu->setStatus( Pressed );
		actionEvent.setSource(*activeMenu);
	}

//Testa MenuItem
	for (int i = 0; i < miAntal; i++ )
		if (activeMenu->getNr() == menuItem[i]->getHeadMenu() && activeMenu->getStatus() == Pressed)
		{
			menuItem[i]->test(y_mouse);
			if (menuItem[i]->getStatus() == Active)
			{ activeMenuItem = menuItem[i];	}
		}

	if (!(mouse_b & 1) && activeMenuItem->getStatus() == Active)
	{
		activeMenuItem->setStatus( Pressed );
		actionEvent.setSource(*activeMenuItem);
		activeMenu->setStatus( Null );
	}

	if (mouse_b & 1 && !(x_mouse >= activeMenu->getLeft() && x_mouse <= activeMenu->getMenuRight()
		&& y_mouse >= activeMenu->getTop() && y_mouse <= activeMenu->getMenuBottom())
		&& activeMenuItem->getStatus() != Active)
		{ activeMenu->setStatus( Null ); }

//Testa Buttons
	for (int i = 0; i < bAntal; ++i)
		if(y_mouse >= button[i]->getTop() && y_mouse <= button[i]->getBottom()
		   && x_mouse >= button[i]->getLeft() && x_mouse <= button[i]->getRight() )
		{
			if (activeButton->getStatus() != Active )
			{
				activeButton->setStatus( Null );
				button[i]->setStatus( Hoover );
				activeButton = button[i];

				if (mouse_b & 1)
					{ activeButton->setStatus( Active ); }
			}
		}
		else { button[i]->setStatus( Null ); }

	if (!(mouse_b & 1) && activeButton->getStatus() == Active)
	{
		activeButton->setStatus( Pressed );
		actionEvent.setSource(activeButton);
		activeButton->setStatus( Null );
	}

//Ritar ut allt på skärmen
	rita.all();
//annvänder det man skrivit i actionhandler
	ActionHandler(actionEvent);	//Hanterar det man skrivit i ActionHandler funktionen
}
