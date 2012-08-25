/*
 *    Example program for the Allegro library, by Shawn Hargreaves.
 *
 *    This program demonstrates how to write directly to video memory.
 *    It implements a simple fire effect, first by calling getpixel() and
 *    putpixel(), then by accessing video memory directly a byte at a
 *    time, and finally using block memory copy operations.
 */


//#include <stdlib.h>
//#include <stdio.h>

#ifdef DJGPP
#include <sys/farptr.h>
#include <sys/segments.h>
#include <sys/movedata.h>
#endif

   PALLETE pal;
   BITMAP *buffer;
   BITMAP *screen_buffer;

/* The fire is formed from several 'hotspots' which are moved randomly
 * across the bottom of the screen.
 */
#define FIRE_HOTSPOTS   48

int hotspot[FIRE_HOTSPOTS];



/* This function updates the bottom line of the screen with a pattern
 * of varying intensities which are then moved upwards and faded out
 * by the code in main().
 */
void draw_bottom_line_of_fire()
{
   int c, c2;
   unsigned char temp[320];

   /* zero the buffer */
   for (c=0; c<SCREEN_W; c++)
      temp[c] = 0;

   for (c=0; c<FIRE_HOTSPOTS; c++) {
      /* display the hotspots */
      for (c2=hotspot[c]-20; c2<hotspot[c]+20; c2++)
    if ((c2 >= 0) && (c2 < SCREEN_W))
       temp[c2] = MIN(temp[c2] + 20-ABS(hotspot[c]-c2), 192);

      /* move the hotspots */
      hotspot[c] += (random() & 7) - 3;
      if (hotspot[c] < 0)
    hotspot[c] += SCREEN_W;
      else
    if (hotspot[c] >= SCREEN_W)
       hotspot[c] -= SCREEN_W;
   }

   /* display the buffer */
   for (c=0; c<SCREEN_W; c++)
      putpixel(screen, c, SCREEN_H-1, temp[c]);
}

int intro()
{
   PALLETE pallete;
   int x, y, c, d, textColor, text = 1, textMitt;
   unsigned long address;
   unsigned char temp[320];
   char * texten;
   double speed, textX, textY = 40;

   set_gfx_mode(GFX_AUTODETECT, 320, 200, 0, 0);

   buffer = create_bitmap(SCREEN_W, 50);
   screen_buffer = create_bitmap(SCREEN_W, SCREEN_H);

   for (c=0; c<FIRE_HOTSPOTS; c++)
      hotspot[c] = random() % SCREEN_W;

   /* fill our pallete with a gradually altering sequence of colors */
   for (c=0; c<64; c++) {
      pallete[c].r = 0;
      pallete[c].g = 0;
      pallete[c].b = c;
   }
   for (c=64; c<128; c++) {
      pallete[c].r = 0;
      pallete[c].g = c-64;
      pallete[c].b = 63;
   }
   for (c=128; c<192; c++) {
      pallete[c].r = c-192;
      pallete[c].g = 63;
      pallete[c].b = 63;
   }
   for (c=192; c<256; c++) {
      pallete[c].r = 63;
      pallete[c].g = 63;
      pallete[c].b = 63;
   }

   set_pallete(pallete);

   speed = retrace_count + 32;

   clear_keybuf();

   /* it's even faster if we transfer the data in big blocks */
   while (!keypressed()) {

      draw_bottom_line_of_fire();

      for (y=50; y<SCREEN_H-1; y++) {
         /* get an address for reading line y+1 */
         address = bmp_read_line(screen, y+1);

         /* read the line */
         movedata(screen->seg, address, _my_ds(), (unsigned)temp, SCREEN_W);

         /* adjust it */
         for (x=0; x<SCREEN_W; x++)
            if (temp[x] > 0)
               temp[x]--;

         /* get an address for writing line y */
         address = bmp_write_line(screen, y);

         /* write the line */
         movedata(_my_ds(), (unsigned)temp, screen->seg, address, SCREEN_W);
      }
      if (text == 1) { texten = "Unlegal!!!";}
      if (text == 2) { texten = "The Ultimate Drugwar";}
      if (text == 3) { texten = "By:";}
      if (text == 4) { texten = "Ande_Vega!!!";}
      if (text == 5) { texten = "And";}
      if (text == 6) { texten = "Kristoffer Fält!!!";}
      if (text == 7) { break; }

      textMitt = (SCREEN_W / 2)-(text_length(font, texten)/2);

      if (textY < -10){text++; textY = 40; textX = speed = retrace_count + 32;}

      textX = 320-2*(retrace_count-speed);

      if (textX < 40) { textY -= 1.5; }
      if (textX < textMitt) { textX = textMitt;}

      clear(buffer);
      select_palette(pal);
      textout(buffer, font, texten, textX, textY, 255);
      blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
      unselect_palette();
   }

   destroy_bitmap(buffer);
   destroy_bitmap(screen_buffer);

   return 0;
}
