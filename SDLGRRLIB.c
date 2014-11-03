/********************************************************************************************
   _____       _____       _     _____                _                    
  / ____|     |  __ \     | |   |  __ \              | |                   
 | |  ____  __| |__) |__ _| |__ | |__) |___ _ __   __| | ___ _ __ ___ _ __ 
 | | |_ \ \/ /|  _  // _` | '_ \|  _  // _ \ '_ \ / _` |/ _ \ '__/ _ \ '__|
 | |__| |>  < | | \ \ (_| | |_) | | \ \  __/ | | | (_| |  __/ | |  __/ |   
  \_____/_/\_\|_|  \_\__, |_.__/|_|  \_\___|_| |_|\__,_|\___|_|  \___|_|   
                      __/ |                                                
                     |___/           
GRRLIB Version : 1.6

Coder : NoNameNo
	uschghost
                 
info : http://wiibrew.org/index.php?title=Homebrew_apps/GRRLIB                   
********************************************************************************************/

#include <SDL/SDL_gfxPrimitives.h>
#include <gccore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <malloc.h>

#include <SDL/SDL.h>

#include "GRRLIB.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
//#include <sdcard.h>


static unsigned Seed1;
static unsigned Seed2;

u16 *GRRLIB_buffer;
u16 GRRLIB_magenta=0xf01e;


u16 *GRRLIB_MakeBuffer(int w, int h)
{
    SDL_SetVideoMode(w, h, 0, SDL_SWSURFACE);
}


void GRRLIB_Start()
{

}

void GRRLIB_Render()
{
    SDL_Flip(SDL_GetVideoSurface());

    SDL_Event ev = { 0 };

    while(SDL_PollEvent(&ev))
    {
        if(ev.type == SDL_QUIT)
        {
            exit(0);
        }
    }
}

void GRRLIB_FillScreen(u16 color){
    SDL_FillRect(SDL_GetVideoSurface(), NULL, color);
}

u32 GRRLIB_Conv565_888(u16 color);

void GRRLIB_PutPixel(int x,int y, u16 pixel){
    int colour = GRRLIB_Conv565_888(pixel);
    pixelColor(SDL_GetVideoSurface(), x, y, colour);
}


void GRRLIB_Line(short int x1, short int y1, short int x2, short int y2, u16 color){
    lineColor(SDL_GetVideoSurface(), x1, y1, x2, y2, GRRLIB_Conv565_888(color));
}

void GRRLIB_DrawImg(int xpos, int ypos, int width, int high, const u16 data[], float rad_ang, float rapport ){
 int ni=0;
 int mx, my, mxdest, mydest;    /* Coordonnées des centres des surfaces */
 int i=0, j;                    /* Coordonnées de travail lors du parcourt de la surface de destination */
 unsigned int bx, by;           /* Coordonnées de travail, correspondent à i et j dans l'image d'origine */
 int x, y;                      /* valeurs de travail (bx et by avant arrondit */
 int ligne_x, ligne_y;          /* valeurs au debut des lignes (retour de i à 0) */
 int dxi, dyi, dxj, dyj;        /* increments des x et y suivant i et j (compteurs des x et y) */
 float tcos, tsin;              /* cos et sin de angle_radian */
 int largeurdest, hauteurdest;  /* Dimentions de la surface de destination */

   if((rad_ang==0)&(rapport==1)){
	 for(y=ypos;y<ypos+high;y++){
                for(x=xpos;x<xpos+width;x++){
						if(data[ni]!=GRRLIB_magenta)
                        GRRLIB_PutPixel(x,y,data[ni]);
                        ni++;
                }
        }	
   }
   else{
        tcos = cos(rad_ang);
        tsin = sin(rad_ang);

        largeurdest = (int) ceil( (width * fabs(tcos) + high * fabs(tsin)) * rapport );
        hauteurdest = (int) ceil( (width * fabs(tsin) + high * fabs(tcos)) * rapport );

        mxdest = (int) largeurdest/2;
        mydest = (int) hauteurdest/2;
        mx = (int) width/2;
        my = (int) high/2;

        /* Initialisation et calculs des incréments */
        ligne_x = mx*65536 + (-tcos * mxdest - tsin * mydest) / rapport * 65536.0;
        ligne_y = my*65536 + ( tsin * mxdest - tcos * mydest) / rapport * 65536.0;
        dxi = tcos / rapport * 65536.0;
        dxj = tsin / rapport * 65536.0;
        dyi = -tsin / rapport * 65536.0;
        dyj = tcos / rapport * 65536.0;

        for(j=0;j<hauteurdest;j++){
                x = ligne_x;
                y = ligne_y;
                for(i=0;i<largeurdest;i++) {
                        bx = ((unsigned int) x) >> 16;
                        by = ((unsigned int) y) >> 16;
                        /* on vérifie que l'on ne sort pas des bords*/
                        if (bx>=0 && bx< width && by>=0 && by< high){
								if(data[by*width+bx]!=GRRLIB_magenta)
                                GRRLIB_PutPixel(i+xpos-mxdest+mx,j+ypos-mydest+my,data[by*width+bx]);
                        }

                                /* On incrémente les coordonnées dans l'image d'origine */
                        x += dxi;
                        y += dyi;
                }
                /* incrément pour le changement de ligne */
                ligne_x += dxj;
                ligne_y += dyj;
        }

   }
}




void GRRLIB_DrawTile(int xpos, int ypos, int width, int high, const u16 data[], int frame, float rad_ang, float rapport ){
 int ni=(width*high*frame);
 int mx, my, mxdest, mydest;    /* Coordonnées des centres des surfaces */
 int i=0, j;                    /* Coordonnées de travail lors du parcourt de la surface de destination */
 unsigned int bx, by;           /* Coordonnées de travail, correspondent à i et j dans l'image d'origine */
 int x, y;                      /* valeurs de travail (bx et by avant arrondit */
 int ligne_x, ligne_y;          /* valeurs au debut des lignes (retour de i à 0) */
 int dxi, dyi, dxj, dyj;        /* increments des x et y suivant i et j (compteurs des x et y) */
 float tcos, tsin;              /* cos et sin de angle_radian */
 int largeurdest, hauteurdest;  /* Dimentions de la surface de destination */

   if((rad_ang==0)&(rapport==1)){
	for(y=ypos;y<ypos+high;y++){
				for(x=xpos;x<xpos+width;x++){
						if(data[ni]!=GRRLIB_magenta)
							GRRLIB_PutPixel(x,y,data[ni]);
						ni++;
                }
        }
   }
   else{
        tcos = cos(rad_ang);
        tsin = sin(rad_ang);

        largeurdest = (int) ceil( (width * fabs(tcos) + high * fabs(tsin)) * rapport );
        hauteurdest = (int) ceil( (width * fabs(tsin) + high * fabs(tcos)) * rapport );

        mxdest = (int) largeurdest/2;
        mydest = (int) hauteurdest/2;
        mx = (int) width/2;
        my = (int) high/2;

        /* Initialisation et calculs des incréments */
        ligne_x = mx*65536 + (-tcos * mxdest - tsin * mydest) / rapport * 65536.0;
        ligne_y = my*65536 + ( tsin * mxdest - tcos * mydest) / rapport * 65536.0;
        dxi = tcos / rapport * 65536.0;
        dxj = tsin / rapport * 65536.0;
        dyi = -tsin / rapport * 65536.0;
        dyj = tcos / rapport * 65536.0;

        for(j=0;j<hauteurdest;j++){
                x = ligne_x;
                y = ligne_y;
                for(i=0;i<largeurdest;i++) {
                        bx = ((unsigned int) x) >> 16;
                        by = ((unsigned int) y) >> 16;
                        /* on vérifie que l'on ne sort pas des bords*/
                        if (bx>=0 && bx< width && by>=0 && by< high){
								if(data[by*width+bx]!=GRRLIB_magenta)
                                GRRLIB_PutPixel(i+xpos-mxdest+mx,j+ypos-mydest+my,data[by*width+bx+(width*high*frame)]);
                        }

                                /* On incrémente les coordonnées dans l'image d'origine */
                        x += dxi;
                        y += dyi;
                }
                /* incrément pour le changement de ligne */
                ligne_x += dxj;
                ligne_y += dyj;
        }

   }
}

void GRRLIB_DrawMap(int xsize, int ysize, int map[],const u16 tdata[] ,int tsize,int scrollx, int scrolly){
	int m,n;

	for(m=0;m<=(xsize-1);m++)
		for(n=0;n<=(ysize-1);n++)
			GRRLIB_DrawTile((m*tsize)+scrollx,(n*tsize)+scrolly,tsize,tsize,tdata,map[m+n*xsize],0,1);

}


void GRRLIB_DrawRectangle(int x, int y, int hight, int widht, u16 color, int filled)
{
	int i;
	if(filled==0)
	{
		GRRLIB_Line(x, y, x + widht, y, color);
		GRRLIB_Line(x, y, x, y + hight, color);
		GRRLIB_Line(x, y+ hight, x + widht, y + hight, color);
		GRRLIB_Line(x + widht, y, x + widht, y + hight, color);
	}
	else
	{
		for(i=0;i<=hight;i++)
			GRRLIB_Line(x, y+i, x + widht, y+i, color);
	}
}

void GRRLIB_DrawTriangle(int x, int y, int xa, int ya, int xb, int yb, u16 color)
{
	GRRLIB_Line(x, y, xa, ya, color);
	GRRLIB_Line(x, y, xb, yb, color);
	GRRLIB_Line(xa, ya, xb, yb, color);
}



int GRRLIB_GetMapTile(int x, int y, int map[],int mapwidth)
{
	return map[x+y*mapwidth];
}










u16 GRRLIB_Conv888_565(u32 colorin){
	u16 colorout;
	u8 r,g,b;

	r = (((colorin >> 16) & 0xFF)*31)/255;
	g = (((colorin >> 8) & 0xFF)*63)/255;
	b = (((colorin) & 0xFF)*31)/255;
	colorout=(((r<<6)|g)<<5)|b;

	return(colorout);	
}

u32 GRRLIB_Conv565_888(u16 colorin)
{
    unsigned char r = (((colorin)&0x01F) <<3);
    unsigned char g = (((colorin)&0x03E0) >>2);
    unsigned char b = (((colorin)&0x7C00 )>>7);
    return (r << 8) + (g << 16) + (b << 24) + 255;
}

unsigned GRRLIB_Rand(unsigned long MAX)
{
        Seed1 = (Seed1 + 46906481) ^ Seed2;
        Seed2 = Seed1 ^ ( ((Seed2<<3) | (Seed2 >> 29)) + 103995407);
        return (Seed1 - Seed2)%MAX;
}
























//********************************************************************************************
// ALL CODE ABOVE THIS LINE IS THE "GX RGB RENDERER" CORE !!!!!!!!!!!!!!!!!!!! DONT TOUCH !!!!
//********************************************************************************************

void GRRLIB_InitVideo () 
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetVideoMode(640, 480, 0, SDL_SWSURFACE);
}


void GRRLIB_Print(int x, int y, int xsize, int ysize,char* text,const u16 tdata[], int fg, int bg){
	int px,py;
	int ni;
	int i;

	for(i=0;i<strlen(text);i++){	
		ni=(xsize*ysize*(text[i]-1));
		for(py=y;py<y+ysize;py++){
			for(px=x;px<x+xsize;px++){
				if(tdata[ni]==0xffff)
                			GRRLIB_PutPixel(px+i*xsize,py,bg);
				else
					GRRLIB_PutPixel(px+i*xsize,py,fg);
                		ni++;
                	}	
         	}
	}
}

void GRRLIB_ImgPrint(int x, int y, int xsize, int ysize,char* text,const u16 tdata[]){
        int i;
        for(i=0;i<strlen(text);i++){
                GRRLIB_DrawTile(x+i*xsize,y,xsize,ysize,tdata,text[i]-32,0,1);
        }
}

/**********************************************************************************
*
* The "hidden" ScreenShoter Routine is here ;)
*
***********************************************************************************/


