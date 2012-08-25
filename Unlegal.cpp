			///////////////////////////////////////////////////////////
			//																			//
			//			Fil: "Unlegal.cpp"										//
			//																			//
			//			Författad av: Andreas Sehr 2001,09,15				//
			//																			//
			//			Senast ändrad:	2002,02,25								//
			//																			//
			//			Version: 0.6												//
			//																			//
			//																			//
			//																			//
			///////////////////////////////////////////////////////////

#include <iostream.h>
#include "Addes.hpp"
#include "Intro.hpp"


#define TOP 0
#define BOTTOM 480
#define LEFT 0
#define RIGHT 640


BITMAP *layout;
BITMAP *mouse_pointer;
SAMPLE *the_sample;

//Mus Egenskaper
int x_mouse = 320;
int y_mouse = 240;
const float sensitivity = 1.25;
const float shake_strength = 0;
int mouse_move_x = 0;
int mouse_move_y = 0;
//bool mouseTwo = false;


float shakescr = 0;

int day = 0;
int money = 1000;
int max_pocket = 100;
const int maxmoney = 100000000;
float allmoney;
int spruta = 1;


struct {
	float x;
    float y;
    double dir;
    double dirylength;
} gold[5000];

struct {
	int buyPrice;
	char *name;
	int bought;
	int availableToBuy;
	int price_rng_min;
    int price_rng_max;
    int price;
	int exist;
} drug[10];


//Funktioner
void set_drug_valuables();
void check_scroll(int& x_mouse, int& y_mouse);
void refreshDrugs();
void refreshList();
void set_gold();
void draw_gold();
void init();
void objektEgenskaper();
void funcBuy();
void quit();


//Knappar
Button oj("oj", 10,10);
Button* endDay;
Button* bQuit;
Button* buy;
Button* buy1;
Button* buy10;
Button* buyAll;
Button* sell;

Radio buyButtons;


//Menyn
MenuBar mainMenuBar;

Menu menuFile("File");
MenuItem nyttSpel("Nytt Spel");
MenuItem oppna("Öppna");
MenuItem spara("Spara");
MenuItem avslut("Avsluta");

Menu menuOptions("Options");
MenuItem andraFarger("Ändra Färger");
MenuItem andraSprak("Ändra Språk");

//Listor
List buyDrugList;
List sellDrugList;
List actionBox;



//-------------------------------------------Main---------------------------------------------
int main(int argc, char *argv[]) {
	allegro_init();
	install_keyboard();
	install_timer();
	layout = load_bmp("layout.1bm",pal);

//	intro();

	install_mouse();
	set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0);
	text_mode(-1);
	bmp = create_bitmap(640, 480);
	clear (bmp);
	mouse_pointer = load_bmp("mouse1.1bm",pal);
	layout = load_bmp("layout.1bm",pal);
	set_pallete(pal);

	init();

	if (install_sound(DIGI_AUTODETECT, MIDI_NONE, argv[0]) != 0) {
		printf("Error initialising sound system\n%s\n", allegro_error);
		return 1;
	}

	the_sample = load_sample("Klick.wav");
	if (!the_sample) {
		printf("Error reading WAV file '%s'\n", "Klick.wav");
	  return 1;
	}

	while (!key[KEY_F5])
	{
		get_mouse_mickeys(&mouse_move_x, &mouse_move_y);
		x_mouse += int (mouse_move_x*sensitivity);
		y_mouse += int (mouse_move_y*sensitivity);
		check_scroll(x_mouse, y_mouse);
		actionListener.listen(y_mouse, x_mouse);
		draw_sprite(bmp, mouse_pointer, x_mouse, y_mouse);
		blit(bmp, screen, 0, 0, 0-int (shakescr), 0-int (shakescr), 640-int (shakescr), 480-int (shakescr));
		clear(bmp);
		draw_sprite(bmp, layout, 0, 0);
		refreshList();
		spruta += 2;
		draw_gold();

        if (shakescr > 0) shakescr--;
        if (shakescr < 0) shakescr++;
	}
}


void check_scroll(int& x_mouse, int& y_mouse)
{
// Kollar så att musen inte åker utabför skärmen.
 	if (x_mouse < LEFT)   { x_mouse = LEFT;    }
 	if (x_mouse > RIGHT)  { x_mouse = RIGHT;   }
 	if (y_mouse < TOP)    { y_mouse = TOP;     }
 	if (y_mouse > BOTTOM) { y_mouse = BOTTOM;  }
}


void set_drug_valuables()
{
    drug[0].price_rng_min = 1000;   drug[0].price_rng_max = 5000;
    drug[1].price_rng_min = 14000;  drug[1].price_rng_max = 30000;
    drug[2].price_rng_min = 500;    drug[2].price_rng_max = 1500;
    drug[3].price_rng_min = 5000;   drug[3].price_rng_max = 14000;
    drug[4].price_rng_min = 1;      drug[4].price_rng_max = 120;
    drug[5].price_rng_min = 1000;   drug[5].price_rng_max = 5000;
    drug[6].price_rng_min = 500;    drug[6].price_rng_max = 1200;
    drug[7].price_rng_min = 1000;   drug[7].price_rng_max = 4000;
    drug[8].price_rng_min = 100;    drug[8].price_rng_max = 500;
    drug[9].price_rng_min = 200;    drug[9].price_rng_max = 700;

	drug[0].name = "Acid   ";
	drug[1].name = "Cocaine";
	drug[2].name = "Hashish";
	drug[3].name = "Heroin ";
	drug[4].name = "Ecstasy";
	drug[5].name = "Smack  ";
	drug[6].name = "Opium  ";
	drug[7].name = "Crack  ";
	drug[8].name = "Peyote ";
	drug[9].name = "Speed  ";
}

void refreshDrugs()
{
	for (int i = 0; i < 10;i++)
	{
        drug[i].price = random() % (drug[i].price_rng_max - drug[i].price_rng_min);
        drug[i].price += drug[i].price_rng_min;
        drug[i].exist = int(random() % 100);
	}
}

void refreshList()
{
	for (int i = 0; i < 10; ++i)
	{
		char tempChar[70];
		sprintf(tempChar,"%7s %5d$ %5d", drug[i].name, drug[i].price, drug[i].exist);
		buyDrugList.setListObjektString(i+1, tempChar);
	}

	for (int i = 0; i < 10; ++i)
	{
		char tempChar[70];
		sprintf(tempChar,"%7s %5d$ %5d", drug[i].name, drug[i].buyPrice, drug[i].bought);
		sellDrugList.setListObjektString(i+1, tempChar);

		if (drug[i].bought > 0 && sellDrugList.getActiveListObjekt().getStatus() != Active)
			{ sellDrugList.setListObjektStatus(i+1, Null); }
		else if (drug[i].bought == 0)
			{ sellDrugList.setListObjektStatus(i+1, NotPressable); }
	}

	char tempChar[70];
	int place = 0;
	sprintf(tempChar,"Day: %d  Money: %d", day, money);
	actionBox.setListObjektString(place++, tempChar);
	sprintf(tempChar,"X_M: %d Y_M: %d", x_mouse, y_mouse );
	actionBox.setListObjektString(place++, tempChar);
	sprintf(tempChar,"gold[0].x: %d  gold[0].y: %d", int(gold[0].x), int(gold[0].y));
	actionBox.setListObjektString(place++, tempChar);
	sprintf(tempChar,"Active lObjekt: %d", sellDrugList.getActiveListObjektNr());
	actionBox.setListObjektString(place++, tempChar);
}

void init()
{
	set_drug_valuables();
	refreshDrugs();
	objektEgenskaper();
	set_gold();
}


void objektEgenskaper()
{
	menuFile.add(nyttSpel);
	//nyttSpel.setStatus(NotPressable);
	//menuFile.add(oppna);
	oppna.setStatus(NotPressable);
	//menuFile.add(spara);
	spara.setStatus(NotPressable);
	menuFile.add(avslut);
	mainMenuBar.add(menuFile);

	menuOptions.add(andraFarger);
	menuOptions.add(andraSprak);
	//mainMenuBar.add(menuOptions);


	endDay = new Button("End Day", 445, 345);
	endDay->setMargin(12);
	endDay->setWidth(80);
	bQuit = new Button("Quit", 445, 415);
	bQuit->setMargin(12);
	bQuit->setWidth(80);
	buy = new Button("Buy", 535, 345);
	buy->setMargin(12);
	buy->setWidth(72);

	buy1 = new Button("1", 535, 380);
	buy1->setMargin(3);
	buy10 = new Button("10", 552, 380);
	buy10->setMargin(3);
	buyAll = new Button("1/1", 577,380);
	buyAll->setMargin(3);
	sell  = new Button("Sell", 535, 415);
	sell->setMargin(12);
	sell->setWidth(72);

	buyButtons.add(*buy1);
	buyButtons.add(*buy10);
	buyButtons.add(*buyAll);

	buyDrugList.setTop(60);
	buyDrugList.setLeft(200);
	buyDrugList.setWidth(205);

	char tempChar[70];
	sprintf(tempChar,"Drug:   Cost:  Available:");
	buyDrugList.add(tempChar);
	buyDrugList.setListObjektStatus(0, NotPressable);
	for (int i = 0; i < 10; ++i)
	{
		sprintf(tempChar,"%s  Cost: %d$  Available: %d", drug[i].name, drug[i].price, drug[i].exist);
		buyDrugList.add(tempChar);
	}

	sellDrugList.setTop(60);
	sellDrugList.setLeft(425);
	sellDrugList.setWidth(190);
	sellDrugList.setStatus(NotPressable);

	sprintf(tempChar,"Drug:     Cost:   Got:");
	sellDrugList.add(tempChar);
	for (int i = 0; i < 10; ++i)
	{
		sprintf(tempChar,"%s %d$  No: %d", drug[i].name, drug[i].buyPrice, drug[i].bought);
		sellDrugList.add(tempChar);
	}

	actionBox.setTop(245);
	actionBox.setLeft(30);
	actionBox.setWidth(250);
	actionBox.setStatus(NotPressable);

	sprintf(tempChar,"Day: %d  Money: %d", day, money);
	actionBox.add(tempChar);
	sprintf(tempChar,"X_M: %d Y_M: %d", x_mouse, y_mouse );
	actionBox.add(tempChar);
	sprintf(tempChar,"gold[0].x: %d  gold[0].y: %d", gold[0].x, gold[0].y);
	actionBox.add(tempChar);
	actionBox.add("BUHUMuhu");

	actionListener.add(buyDrugList);
	actionListener.add(sellDrugList);
	actionListener.add(actionBox);
	actionListener.add(bQuit);
	actionListener.add(endDay);
	actionListener.add(buy);
	actionListener.add(buyButtons);
	actionListener.add(sell);
	actionListener.add(nyttSpel);
	//actionListener.add(oppna);
	//actionListener.add(spara);
	actionListener.add(avslut);
	actionListener.add(menuFile);
	//actionListener.add(andraFarger);
	//actionListener.add(andraSprak);
	//actionListener.add(menuOptions);
	actionListener.add(mainMenuBar);
}

void ActionHandler(ActionEvent &ev)
{
	if (ev.buttons())
		{ play_sample(the_sample, 128, 128, 1000, FALSE); }

	if (ev == avslut)
		{ quit(); }

	if (ev == nyttSpel)
		cirkel();

	if (ev == endDay)
	{
		day++;
		shakescr = random() % 2;
		if (shakescr == 1)
			shakescr = shake_strength;
		if (shakescr == 0)
			shakescr = 0-shake_strength;
		refreshDrugs();
		set_gold();
        spruta = 1;
	}

	if (ev == sell)
	{
		const int selected = sellDrugList.getActiveListObjektNr()-1;

		for (;drug[selected].bought > 0; drug[selected].bought--)
		{
	        money += drug[selected].price;
	        drug[selected].exist += 1;
		}
		drug[selected].buyPrice = 0;
    }

	if (ev == buy)
		funcBuy();

	if (ev == bQuit)
		quit();

	ev.setNull();
}

void funcBuy()
{
	const int selected = buyDrugList.getActiveListObjektNr()-1;
	int toBuy = 0;

	if (buyButtons.getActiveButton() == buy1)
		{ toBuy = 1; }
	if (buyButtons.getActiveButton() == buy10)
		{ toBuy = 10; }
	if (buyButtons.getActiveButton() == buyAll)
			{ toBuy = max_pocket; }

	for(int A = 0;drug[selected].bought < max_pocket && drug[selected].exist > 0
		 	 && A < toBuy && money >= drug[selected].price;	A++)
	{
		drug[selected].bought += 1;
		drug[selected].exist -= 1;
		drug[selected].buyPrice = drug[selected].price;
		money -= drug[selected].price;
	}
}

void quit()
{
   	destroy_sample(the_sample);
	delete endDay; delete bQuit; delete buy; delete sell;

	clear(screen);
	textout(screen, font, "Thanks for playing Unlegal                    [Press Enter]", 60, 200, WHITE);
	textout(screen, font, "___________________________________________________________________________________________________________", 0, 12, WHITE);
	textout(screen, font, "Unlegal was made by", 270, 10, WHITE);
	textout(screen, font, "¤   Andreas Sehr, ande_vega@hotmail.com", 75, 30, WHITE);
	textout(screen, font, "¤   Original Version: Sebastian Sehr, wiz.westside@usa.net", 75, 50, WHITE);
	textout(screen, font, "¤¤¤   This is a great game!!! Isn't it...   ¤¤¤", 40, 370, WHITE);
//	while (!key[KEY_ENTER]);
//	while (key[KEY_ENTER]);
	allegro_exit();
	exit(0);
}




//Oförandrad kod från sebbe
void set_gold()
{
	allmoney = money * 0.001;
	if (allmoney > maxmoney)
		{ allmoney = maxmoney; }

	for (int i = 0; i < allmoney; i++)
	{
		gold[i].x = 210;
		gold[i].y = 350;
		gold[i].dir = (random() % 35000)+10000;
		gold[i].dir *= 0.0001;
		gold[i].dirylength = 0;
		gold[i].dirylength = (random() % 20000)-10000;
		gold[i].dirylength *= 0.0001;
	}
}


void draw_gold()
{
	if (spruta > allmoney) spruta = int (allmoney);
		for (int i = 0; i < spruta; i++)
		{
			gold[i].dirylength += 0.1;
			if (gold[i].dirylength > 1)
				{ gold[i].dirylength = 1; }
			if (getpixel(screen, (int) gold[i].x, (int) gold[i].y+1) == 0)
				{ gold[i].y+=gold[i].dirylength; }
			if (getpixel(screen, (int) gold[i].x, (int) gold[i].y+1) > 0 && gold[i].dirylength > 0)
				{ gold[i].dirylength = gold[i].dirylength - (gold[i].dirylength*1.5); }

			if (getpixel(screen, (int) gold[i].x+1, (int) gold[i].y) > 0 && gold[i].dir > 0)
				{ gold[i].dir = gold[i].dir - (gold[i].dir*2); }
			else if (getpixel(screen, (int) gold[i].x-1, (int) gold[i].y) > 0
					&& gold[i].dir < 0) gold[i].dir = gold[i].dir - (gold[i].dir*2);
				{ gold[i].x+=gold[i].dir; }

			if (gold[i].dir > 0)
				{ gold[i].dir-=0.01;}
			if (gold[i].dir < 0)
				{ gold[i].dir+=0.01; }

			if (gold[i].x < 210)
			{
				gold[i].x = 210;
				gold[i].dir = gold[i].dir - (gold[i].dir*2);
			}
			if (gold[i].x > 397)
			{
				gold[i].x = 397;
				gold[i].dir = gold[i].dir - (gold[i].dir*2);
			}
			if (gold[i].y > 436)
				{ gold[i].y = 436; }

			putpixel(bmp,(int) gold[i].x, (int) gold[i].y, 137);
		}
}
