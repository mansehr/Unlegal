			//////////////////////////////////////////////////////////
			//														//
			//			Fil: "Menu.hpp"								//
			//														//
			//			Författad av: Andreas Sehr 2001,10,17		//
			//														//
			//			Senast ändrad:	2002,01,07					//
			//														//
			//////////////////////////////////////////////////////////

//-------------------------------------------Class MenuItem---------------------------------------------
class MenuItem : public Objekt
{
	public:
		MenuItem() {;}
		MenuItem (char *initText) {setText(initText);}

		int getIndrag() const {return indrag;}
		int getHeadMenu() const {return headMenu;}

		void setIndrag (int initIndrag) {indrag = initIndrag;}
		void setHeadMenu(int initHeadMenu) {headMenu = initHeadMenu;}

		bool test(int y_mouse);
		void draw();

	protected:
		int indrag;
		int headMenu;
};

void MenuItem::draw()
{
	int tempTextColor = BLACK;

	if (getStatus() == NotPressable)
		{ tempTextColor = GREY; }
	else if ( getStatus() == Hoover || getStatus() == Active)
	{
		rectfill(bmp, getLeft(), getTop(), getRight(), getBottom(), 22);
		tempTextColor = BLACK;
	}

	textout(bmp, font, getText(), getLeft() + getIndrag(), getTop() + 4, tempTextColor);
}

bool MenuItem::test(int y_mouse)
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
	else
	{
		if (getStatus() != Active)
		{
			setStatus(Null);
			return false;
		}
		if (!(mouse_b & 1) && getStatus() == Active)
		{
			setStatus(Pressed);
			return true;
		}
	}
}

//-------------------------------------------Class Menu---------------------------------------------
class Menu : public MenuButton
{
	public:
		Menu ();
		Menu (char *initText);
		~Menu();

	 	MenuItem *menuItem[30];
		void add(MenuItem &initMenuItem);
		int biggest(int a, int b);

		int getMenuItemAntal() const {return menuItemAntal;}
		int getMenuTop() const {return menuTop;}
		int getMenuBottom() const {return menuBottom;}
		int getMenuRight() const {return menuRight;}
		int getMenuBredd() const {return menuBredd;}
		int getTextTop() const {return textTop;}
		int getNr() const {return nr;}
		int getHeadMenuBar() const {return headMenuBar;}

		void setMenuItemAntal (int initMIA) {menuItemAntal = initMIA;}
		void setMenuTop (int initMenuTop) {menuTop = initMenuTop;}
		void setMenuBottom (int initMenuBottom) {menuBottom = initMenuBottom;}
		void setMenuRight (int initMR) {menuRight = initMR;}
		void setMenuBredd (int initMenuBredd) {menuBredd = initMenuBredd;}
		void setTextTop (int initTextTop) {textTop = initTextTop;}
		void setHeadMenuBar(int initHeadMenuBar) {headMenuBar = initHeadMenuBar;}

		void draw();
		bool test(int x_mouse, int y_mouse);

		static int menuAntal;

	protected:
		int menuItemAntal;
		int menuTop;
		int menuBottom;
		int menuBredd;
		int menuRight;
		int textTop;
		int headMenuBar;
		int nr;
};

int Menu::menuAntal = 0;

Menu::Menu()
{
	menuItemAntal = 0;
	nr = ++menuAntal;
}


Menu::Menu( char *initText) :
MenuButton::MenuButton(initText)
{
	setMargin(2);
	menuBredd = getWidth();
	menuItemAntal = 0;
	nr = ++menuAntal;

}

Menu::~Menu()
{
	menuAntal--;
}

void
Menu::add(MenuItem &initMenuItem)
{
	int i = menuItemAntal;

	menuItem[i] = &initMenuItem;
	menuItem[i]->setIndrag( 20 );
	menuItem[i]->setTop ( menuBottom + 3);
	menuItem[i]->setBottom( menuItem[i]->getTop() + menuItem[i]->getHeight() + 6  );
	menuItem[i]->setWidth(menuItem[i]->getWidth()  + (2 * menuItem[i]->getIndrag() ) );
	menuItem[i]->setHeadMenu(nr);
	menuBottom = menuItem[i]->getBottom();
	menuBredd =  biggest( menuBredd, menuItem[i]->getWidth() );

	menuItemAntal++;
}

int
Menu::biggest(int a, int b)
{
	if (a > b)
		return a;
	else return b;
}

bool
Menu::test(int x_mouse, int y_mouse)
{

}

void
Menu::draw()
{
	MenuButton::draw();
	if ( getStatus() == Pressed)
	{
		//Ritar upp menurutan
		rectfill(bmp, getLeft(), getMenuTop() + 2, getMenuRight(), getMenuBottom(), GREY);

		line(bmp, getLeft(), getMenuTop() + 1, getLeft(), getMenuBottom(), LIGHTGREY);
		line(bmp, getLeft(), getMenuTop() + 1, getMenuRight(), getMenuTop() + 1, LIGHTGREY);
		line(bmp, getLeft() + 1, getMenuTop() + 2, getLeft() + 1, getMenuBottom() - 1, WHITE);
		line(bmp, getLeft() + 1, getMenuTop() + 2, getMenuRight(), getMenuTop() + 2, WHITE);
		line(bmp, getMenuRight(), getMenuTop() + 1, getMenuRight(), getMenuBottom(), BLACK);
		line(bmp, getLeft(), getMenuBottom(), getMenuRight(), getMenuBottom(), BLACK);
		line(bmp, getMenuRight() - 1, getMenuTop() + 3, getMenuRight() - 1, getMenuBottom() - 1, DARKGREY);
		line(bmp, getLeft() + 1, getMenuBottom() - 1, getMenuRight() - 1, getMenuBottom() - 1, DARKGREY);

		for (int i = 0; i < getMenuItemAntal(); i++)
			menuItem[i]->draw();
	}
}




//-------------------------------------------Class MenuBar---------------------------------------------
class MenuBar : public Objekt
{
	public:
		MenuBar();
		~MenuBar() { --menuBarAntal;}
		void add (Menu &initMenu);
		void draw();

		int getEnd() const {return right;}
		int getBot() const {return bottom;}
		int getMenuAntal() const {return mAntal;}
		int getNr() const {return nr;}

		static int menuBarAntal;

	private:
		Menu *menu[15];

 		int menuTextPos;
 		COLOUR farg1, farg2, farg3, farg4;
		int mAntal;
		int nr;
		Status menuStatus;
};

int MenuBar::menuBarAntal = 0;

MenuBar::MenuBar()
{
	mAntal = 0;
	menuTextPos = 3;
	bottom = 13;
	menuStatus = Null;
	bmp = create_bitmap(640, 480);
	nr = ++menuBarAntal;
}


void MenuBar::add(Menu &initMenu)
{
	int i = mAntal;

	mAntal = i;
	menu[i] = &initMenu;
	menu[i]->setTextTop( bottom + 6 );
	menu[i]->setMenuBottom( menu[i]->getMenuBottom() + bottom + 5);
	menu[i]->setMenuTop(bottom);
	menu[i]->setTop(top);
	menu[i]->setBottom(bottom);
	menu[i]->setLeft( right );
	menu[i]->setRight( ( menu[i]->getLeft() + menu[i]->getWidth() + 8 ) );
	menu[i]->setMenuRight( menu[i]->getLeft() + menu[i]->getMenuBredd() );
	menu[i]->setHeadMenuBar(nr);
	right = menu[i]->getRight();

	for (int z = 0; z <= menu[i]->getMenuItemAntal(); z++)
	{
		menu[i]->menuItem[z]->setTop( menu[i]->menuItem[z]->getTop() + bottom + 2);
		menu[i]->menuItem[z]->setBottom( menu[i]->menuItem[z]->getBottom() + bottom + 2);
		menu[i]->menuItem[z]->setLeft( menu[i]->getLeft() + 3 );
		menu[i]->menuItem[z]->setRight( menu[i]->getMenuRight() - 3);
	}

	mAntal++;
}

void MenuBar::draw()
{
	for ( int i = 0; i < mAntal; ++i)
		menu[i]->draw();
}
